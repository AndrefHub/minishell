/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:34:34 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/14 17:40:17 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_list	*ft_lst_delnext(t_list *prev, t_list *elem, t_list **lst,
	void (*del)(void *))
{
	t_list	*delete;

	if (elem)
	{
		if (prev)
			prev->next = elem->next;
		else if (lst && *lst)
			*lst = (*lst)->next;
		delete = elem;
		elem = elem->next;
		ft_lstdelone(delete, del);
	}
	return (elem);
}

t_list	*ft_rm_space(t_list **lst)
{
	char	*str;
	t_list	*prev;
	t_list	*elem;

	prev = NULL;
	elem = *lst;
	split_by_pattern(&elem, " ", 1);
	split_by_pattern(&elem, "\t", 1);
	while (elem)
	{
		str = elem->content;
		if (!str || !ft_strlen(str) || ft_strchr(" \t", str[0]))
			elem = ft_lst_delnext(prev, elem, lst, free);
		else
		{
			prev = elem;
			elem = elem->next;
		}
	}
	return (*lst);
}

void	ft_com_rm_space(t_command *command)
{
	t_list		*lst;

	lst = command->content;
	command->content = ft_rm_space(&lst);
	command = command->next;
}

void	ft_com_rm_quotes(t_command *cmd, char *quote)
{
	char	*str;
	t_list	*prev;
	t_list	*elem;
	t_list	*lst;

	lst = cmd->content;
	prev = NULL;
	elem = lst;
	split_by_pattern(&elem, quote, -1);
	while (elem)
	{
		str = elem->content;
		if (!str || !ft_strlen(str) || ft_strchr(quote, str[0]))
			elem = ft_lst_delnext(prev, elem, &lst, free);
		else
		{
			prev = elem;
			elem = elem->next;
		}
	}
	cmd->content = lst;
}
