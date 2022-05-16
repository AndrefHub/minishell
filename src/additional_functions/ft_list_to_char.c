/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_to_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:37:37 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/15 15:53:16 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_lstadd_middle(t_list **lst, t_list *add_next, t_list *to_add)
{
	t_list	*tmp;

	if (!add_next || !to_add)
		return ;
	if (add_next->next)
	{
		tmp = add_next->next;
		add_next->next = to_add;
		to_add->next = tmp;
	}
	else
		ft_lstadd_back(lst, to_add);
}

void	ft_list_to_char_ptr(t_command *cmd)
{
	int		counter;
	int		arrsize;
	t_list	*local_copy;
	char	**name_args;

	local_copy = cmd->content;
	arrsize = ft_lstsize(local_copy);
	name_args = malloc(sizeof(*(name_args)) * (arrsize + 1));
	counter = -1;
	while (++counter < arrsize)
	{
		name_args[counter] = (char *)(local_copy->content);
		local_copy = local_copy->next;
	}
	name_args[counter] = NULL;
	cmd->name_args = name_args;
}

void	convert_commands_to_char_ptrs(t_command *cmd)
{
	t_command	*local_copy;

	local_copy = cmd;
	while (local_copy)
	{
		ft_list_to_char_ptr(local_copy);
		local_copy = local_copy->next;
	}
}
