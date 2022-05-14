/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andref <andref@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:36:36 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/14 19:17:56 by andref           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_command	*set_variables(t_command *command)
{
	t_list		*lst;
	t_list		*delete;

	lst = command->content;
	split_by_pattern(&lst, "$");
	while (lst)
	{
		if (strchr(lst->content, '$') && lst->next && ft_strchr
			(lst->next->content, ' ') == NULL)
		{
			if (ft_strchr(lst->next->content, '?'))
				lst->content = ft_strdup(ft_itoa(g_msh.last_ex_code));
			else if (ft_strchr(lst->next->content, '$'))
				lst->content = ft_strdup(ft_itoa(getpid()));
			else
				lst->content = ft_strdup(ft_find_envp(lst->next->content));
			delete = lst->next;
			lst->next = delete->next;
			ft_lstdelone(delete, free);
		}
		lst = lst->next;
	}
	return (command);
}

int	is_in_wildcard_templ(char *string, char *template)
{
	if (*template != '*')
	{
		if (*string)
		{
			if ((*template == '?' || *string == *template)
				&& is_in_wildcard_templ(string + 1, template + 1))
				return (1);
			return (0);
		}
		else
		{
			if (*template == '\0')
				return (1);
			return (0);
		}
	}
	else
	{
		if (is_in_wildcard_templ(string, template + 1)
			|| (*string != '\0' && is_in_wildcard_templ(string + 1, template)))
			return (1);
		return (0);
	}
}

t_list	*ft_list_files(char *name)
{
	DIR				*d;
	t_list			*file_list;
	struct dirent	*dir;

	file_list = NULL;
	d = opendir(name);
	if (d)
	{
		dir = readdir(d);
		while (dir != NULL)
		{
			if (dir->d_name[0] != '.')
				ft_lstadd_back(&file_list, ft_lstnew(ft_strdup(dir->d_name)));
			dir = readdir(d);
		}
		closedir(d);
	}
	return (file_list);
}

t_list	*passed_wildcard_files(char *wildcard, char *pwd)
{
	t_list	*file_list;
	t_list	*passed;
	t_list	*elem;

	file_list = ft_list_files(pwd);
	passed = NULL;
	elem = file_list;
	while (elem)
	{
		if (is_in_wildcard_templ(elem->content, wildcard))
			ft_lstadd_back(&passed, ft_lstnew(ft_strdup(elem->content)));
		elem = elem->next;
	}
	ft_lstclear(&file_list, free);
	return (passed);
}

static void	wild_free_tool(char *path, char *wildcard)
{
	free(path);
	free(wildcard);
}

static void	ft_add_path(t_list *out, char *prev_dir, char *wildcard, char *path)
{
	char	*str;

	while (out)
	{
		str = ft_strjoin(prev_dir, out->content);
		free(out->content);
		out->content = str;
		out = out->next;
	}
	free(prev_dir);
	wild_free_tool(path, wildcard);
}

t_list	*recursive_wild_path(char *wildcard, char *pwd, char *prev_dir)
{
	char	*path;
	t_list	*wilds;
	t_list	*tmp;
	t_list	*out;

	out = NULL;
	path = ft_strndup(wildcard, ft_find_substr(wildcard, "/"));
	wilds = passed_wildcard_files(path, pwd);
	tmp = wilds;
	if (ft_strlen(path) != ft_strlen(wildcard))
	{
		pwd = ft_strjoin_gnl(pwd, "/");
		while (wilds)
		{
			ft_lstadd_back(&out, recursive_wild_path(ft_strdup(&wildcard
					[ft_strlen(path) + 1]), ft_strjoin_gnl(pwd, wilds->content),
					ft_strjoin(wilds->content, "/")));
			wilds = wilds->next;
		}
		ft_lstclear(&tmp, free);
	}
	else
		ft_lstadd_back(&out, tmp);
	ft_add_path(out, prev_dir, wildcard, path);
	return (out);
}

int	ft_add_wildlist(t_list *elem, t_list *prev)
{
	t_list	*wildcard;
	t_list	*tmp;
	char	*pwd;
	char	*m;

	m = ft_strnew(0);
	pwd = ft_strdup(g_msh.pwd);
	wildcard = NULL;
	wildcard = recursive_wild_path(ft_strdup(elem->content), pwd, m);
	if (!wildcard)
		return (0);
	tmp = elem->next;
	ft_lstdelone(elem, free);
	prev->next = wildcard;
	ft_lstlast(wildcard)->next = tmp;
	return (1);
}

void	set_wildcards(t_command *command)
{
	t_list	*elem;
	t_list	*prev;

	while (command)
	{
		prev = command->content;
		elem = command->content->next;
		while (elem)
		{
			if (elem->content && (ft_strchr(elem->content, '*') || ft_strchr
					(elem->content, '?')) && ft_add_wildlist(elem, prev))
				break ;
			prev = elem;
			elem = elem->next;
		}
		command = command->next;
	}
}
