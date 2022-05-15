/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_semicolons.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:36:31 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/15 14:19:05 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_command	*ft_command_split_while(t_list **new_begin, int *counter,
							int link_type)
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

t_command	*ft_command_split(t_command **prev, t_command *to_split,
					int link_type)
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
	t_command	*commands;
	t_command	*new_begin;
	t_command	*prev;
	t_command	*buffer;
	int			counter;

	commands = ft_new_command(lst, ENDING_TYPE);
	counter = SEMICOLON - 1;
	while (++counter < HEREDOC)
	{
		prev = NULL;
		buffer = commands;
		while (commands)
		{
			if (commands == buffer)
				new_begin = ft_command_split(&prev, commands, counter);
			else
				ft_command_split(&prev, commands, counter);
			prev = commands;
			commands = commands->next;
		}
		commands = new_begin;
	}
	return (new_begin);
}

t_command	*parse_redirects_single_command(t_command *command, int link_type)
{
	t_list		*begin;
	t_list		*prev;
	t_list		*tmp;

	split_by_pattern(&(command->content), g_msh.sp_ops[link_type]);
	prev = NULL;
	begin = command->content;
	tmp = command->content;
	while (tmp)
	{
		if (ft_strncmp(((char *) tmp->content), g_msh.sp_ops[link_type],
				ft_strlen(g_msh.sp_ops[link_type])) == 0)
		{
			set_file_in_command(command, link_type, tmp);
			tmp = ft_lst_delnext(prev, tmp, &begin, free);
			tmp = ft_lst_delnext(prev, tmp, &begin, free);
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
	command->content = begin;
	return (command);
}

t_command	*parse_redirects(t_command *commands)
{
	t_command	*tmp;
	int			counter;

	counter = HEREDOC - 1;
	while (++counter < ENDING_TYPE)
	{
		tmp = commands;
		while (tmp)
		{
			parse_redirects_single_command(tmp, counter);
			tmp = tmp->next;
		}
	}
	return (commands);
}
