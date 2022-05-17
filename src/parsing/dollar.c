/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 21:37:03 by lsherry           #+#    #+#             */
/*   Updated: 2022/05/15 21:37:13 by lsherry          ###   ########.fr       */
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

char	*ret_lst_cont(t_list *lst)
{
	char	*str;
	char	*out;
	t_list	*note;

	str = lst->content;
	note = ft_lstnew(ft_strdup(lst->content));
	split_by_pattern(&note, "\"", -1);
	split_by_pattern(&note, "\'", -1);
	note = set_var(note);
	delete_first_and_last(&note);
	out = ft_lst_to_char(note);
	ft_lstclear(&note, free);
	free(str);
	return (out);
}

void	check_end_and_start_one_line(char *line)
{
	int	counter;

	counter = ft_strlen(line);
	while (line[--counter])
	{
		if (!ft_strchr("\t ", line[counter]))
		{
			if (ft_strchr("><|&;", line[counter]))
			{
				fill_error(choose_code(line + counter - 1, 0));
				free(line);
				check_syntax(NULL);
				return ;
			}
			else
				break ;
		}
	}
	check_begin_and_start_one_line(line);
}
