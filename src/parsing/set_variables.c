/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:36:36 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/15 20:49:51 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_lst_to_char(t_list *lst)
{
	char	*str;

	str = malloc(1);
	str[0] = '\0';
	while (lst)
	{
		str = ft_strjoin_gnl(str, (char *)lst->content);
		lst = lst->next;
	}
	return (str);
}

t_list	*set_var(t_list *command)
{
	t_list		*lst;
	t_list		*delete;

	lst = command;
	split_by_pattern(&lst, "$", 1);
	while (lst)
	{
		if (is_dollar(lst))
		{
			if (lst->next->content != NULL)
				free(lst->content);
			if (ft_strchr(lst->next->content, '?'))
				lst->content = ft_itoa(g_msh.last_ex_code);
			else if (ft_strchr(lst->next->content, '$'))
				lst->content = ft_strdup("Command forbidden");
			else
				lst->content = ft_find_envp(lst->next->content);
			delete = lst->next;
			lst->next = delete->next;
			ft_lstdelone(delete, free);
		}
		lst = lst->next;
	}
	return (command);
}

void	delete_first_and_last(t_list **note)
{
	t_list	*new_begin;

	if (!*note || !(*note)->next || !(*note)->next->next)
	{
		ft_lstclear(note, free);
		return ;
	}
	new_begin = (*note)->next;
	ft_lstdelone(*note, free);
	*note = new_begin;
	while (new_begin && new_begin->next && new_begin->next->next)
		new_begin = new_begin->next;
	ft_lstdelone(new_begin->next, free);
	new_begin->next = NULL;
}

t_command	*set_variables(t_command *command)
{
	t_list		*lst;
	t_list		*note;
	char		*str;

	lst = command->content;
	lst = set_var(lst);
	while (lst)
	{
		if (lst->content != NULL && ft_strchr("\'", ((char *)lst->content)[0]) != NULL)
		{
			str = lst->content;
			note = ft_lstnew(ft_strdup(lst->content));
			split_by_pattern(&note, "\'", -1);
			delete_first_and_last(&note);
			lst->content = ft_lst_to_char(note);
			ft_lstclear(&note, free);
			free(str);
		}
		else if (lst->content != NULL && ft_strchr("\"", ((char *)lst->content)[0]) != NULL)
		{
			str = lst->content;
			note = ft_lstnew(ft_strdup(lst->content));
			split_by_pattern(&note, "\"", -1);
			split_by_pattern(&note, "\'", -1);
			note = set_var(note);
			delete_first_and_last(&note);
			lst->content = ft_lst_to_char(note);
			ft_lstclear(&note, free);
			free(str);
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

	prev = command->content;
	elem = prev->next;
	while (elem)
	{
		if (elem->content && (ft_strchr(elem->content, '*') || ft_strchr
				(elem->content, '?')))
		{
			if (!ft_add_wildlist(elem, prev))
				break ;
		}
		prev = elem;
		elem = elem->next;
	}
}
