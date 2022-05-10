/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:34:34 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/10 17:34:39 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_list	*ft_lst_delnext(t_list *prev, t_list *elem, t_list **lst)
{
	t_list	*delete;

	if (prev)
		prev->next = elem->next;
	else
		*lst = (*lst)->next;
	delete = elem;
	elem = elem->next;
	ft_lstdelone(delete, free);
	return (elem);
}

t_list	*ft_rm_space(t_list **lst)
{
	char	*str;
	t_list	*prev;
	t_list	*elem;

	prev = NULL;
	elem = *lst;
	split_by_pattern(&elem, " ");
	split_by_pattern(&elem, "\t");
	while (elem)
	{
		str = elem->content;
		if ((!str || !ft_strlen(str) || ft_strchr(" \t", str[0])))
			elem = ft_lst_delnext(prev, elem, lst);
		else
		{
			prev = elem;
			elem = elem->next;
		}
	}
	return (*lst);
}

void	ft_com_rm_space(t_command *cmd)
{
	t_list		*lst;
	t_command	*command;

	command = cmd;
	while (command)
	{
		lst = command->content;
		command->content = ft_rm_space(&lst);
		command = command->next;
	}
}