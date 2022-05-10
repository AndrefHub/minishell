/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_semicolons.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:36:31 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/10 19:18:07 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	split_by_pattern(t_list **lst, char *pattern)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		ft_split_str_in_lst(pattern, tmp);
		tmp = tmp->next;
	}
}

t_command	*ft_command_split_while(t_list **new_begin, int *counter, int link_type)
{
	t_command	*commands;
	t_list		*tmp;

	commands = NULL;
	tmp = *new_begin;
	while (tmp)
	{
		++(*counter);
		if (ft_strncmp(((char *) tmp->content), g_msh.sp_ops[link_type],
			ft_strlen(g_msh.sp_ops[link_type])) == 0)
		{
			tmp = tmp->next;
			ft_comadd_back(&commands, ft_new_command(ft_lstnsplit(new_begin,
				*counter), link_type));
			(*counter) = 0;
		}
		else
			tmp = tmp->next;
	}
	return (commands);
}

t_command	*ft_command_split(t_command **prev, t_command *to_split, int link_type)
{
	t_command	*commands;
	t_list		*new_begin;
	int			counter;
	
	counter = 0;
	split_by_pattern(&(to_split->content), g_msh.sp_ops[link_type]);
	new_begin = to_split->content;
	commands = ft_command_split_while(&new_begin, &counter, link_type);
	if (counter)
	{
		to_split->content = new_begin;
		ft_comadd_back(&commands, to_split);
	}
	else
		ft_command_last(commands)->next = to_split->next;
	if (*prev)
		(*prev)->next = commands;
	return (commands);
}

t_command	*parse_special_characters(t_list *lst)
{
	t_command	*new_begin;
	t_command	*commands;
	t_command	*prev;
	t_command	*buffer;
	int			counter;

	commands = ft_new_command(lst, ENDING_TYPE);
	// prev = NULL;
	// buffer = commands;
	counter = -1;
	while (++counter < 5)
	{
		prev = NULL;
		buffer = commands;
		while (commands)
		{
			if (commands == buffer)
				new_begin =	ft_command_split(&prev, commands, counter);
			else
				ft_command_split(&prev, commands, counter);
			prev = commands;
			commands = commands->next;
		}
		commands = new_begin;
	}
	return (new_begin);
}
