/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andref <andref@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:37:43 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/15 15:16:33 by andref           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_command	*ft_new_command(t_list *content, int code)
{
	t_command	*command;

	command = (t_command *) malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->content = content;
	command->link_type = code;
	command->infile = NULL;
	command->outfile = NULL;
	command->name_args = NULL;
	command->next = NULL;
	return (command);
}

void	ft_comadd_back(t_command **lst, t_command *new)
{
	t_command	*elem;

	if (*lst)
	{
		elem = *lst;
		while (elem->next)
			elem = elem->next;
		elem->next = new;
	}
	else
		*lst = new;
}

t_command	*ft_command_last(t_command *command)
{
	if (!command)
		return (NULL);
	while (command->next)
		command = command->next;
	return (command);
}

t_list	*ft_lstnsplit(t_list **begin, int n)
{
	t_list	*old_begin;

	old_begin = *begin;
	*begin = ft_lstat(old_begin, n);
	if (n > 1)
	{
		free(ft_lstat(old_begin, n - 1)->content);
		free(ft_lstat(old_begin, n - 1));
		ft_lstat(old_begin, n - 2)->next = NULL;
	}
	else
	{
		free(old_begin->content);
		old_begin->content = ft_strdup("");
		old_begin->next = NULL;
	}
	return (old_begin);
}

void	ft_comclear(t_command **com, int err)
{
	t_command	*elem;
	t_command	*copy;

	copy = *com;
	while (copy)
	{
		elem = copy->next;
		if (copy->content)
			ft_lstclear(&(copy->content), free);
		if (copy->name_args != NULL)
		{
			free(copy->name_args);
			copy->name_args = NULL;
		}
		ft_free_file(copy->infile, err);
		ft_free_file(copy->outfile, err);
		free(copy);
		copy = elem;
	}
	*com = ((void *)0);
}
