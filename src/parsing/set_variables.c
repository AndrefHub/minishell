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

t_command	*set_variables(t_command *command)
{
	t_list		*lst;
	t_list		*note;
	char		*str;

	lst = command->content;
	lst = set_var(lst);
	while (lst)
	{
		if (lst->content != NULL && ft_strchr
			("\'", ((char *)lst->content)[0]) != NULL)
		{
			str = lst->content;
			note = ft_lstnew(ft_strdup(lst->content));
			split_by_pattern(&note, "\'", -1);
			delete_first_and_last(&note);
			lst->content = ft_lst_to_char(note);
			ft_lstclear(&note, free);
			free(str);
		}
		else if (lst->content != NULL
			&& ft_strchr("\"", ((char *)lst->content)[0]) != NULL)
			lst->content = ret_lst_cont(lst);
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

	elem = NULL;
    prev = command->content;
    if (prev)
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
