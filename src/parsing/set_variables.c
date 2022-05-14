/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:36:36 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/10 18:15:19 by kdancy           ###   ########.fr       */
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
				lst->content = ft_strdup(ft_find_envp(lst->next->content,
							g_msh.envp));
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
	(void ) wildcard;
	while (elem)
	{
		if (is_in_wildcard_templ(elem->content, wildcard))
			ft_lstadd_back(&passed, ft_lstnew(ft_strdup(elem->content)));
		elem = elem->next;
	}
	ft_lstclear(&file_list, free);
	return (passed);
}

void	set_wildcards(t_command *command)
{
//	(void ) command;
	t_list	*elem;
	t_list	*prev;
	t_list	*wildcard;
	t_list	*tmp;

	while (command)
	{
		prev = command->content;
		wildcard = NULL;
		elem = command->content->next;
		while (elem)
		{
			if (elem->content && (ft_strchr(elem->content, '*') || ft_strchr(elem->content, '?')))
			{
				wildcard = passed_wildcard_files(elem->content, g_msh.pwd);
				if (!wildcard)
					break;
				tmp = elem->next;
				ft_lstdelone(elem, free);
				prev->next = wildcard;
				ft_lstlast(wildcard)->next = tmp;
			}
			prev = elem;
			elem = elem->next;
		}
		command = command->next;
	}
}