/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parentheses.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andref <andref@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 22:41:03 by lsherry           #+#    #+#             */
/*   Updated: 2022/05/14 18:07:18 by andref           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_list	*parse_parentheses(t_list *quotes)
{
	split_by_pattern(&quotes, "(", 1);
	split_by_pattern(&quotes, ")", 1);
	return (quotes);
}

static void	parse_bracket_tool(t_command *command, t_list *elem, int *br_l,
	int *br_r)
{
	t_list		*prev;

	prev = NULL;
	while (elem)
	{
		if (ft_strchr("(", ((char *)elem->content)[0]))
		{
			br_r += ++command->bracket_l;
			elem = ft_lst_delnext(prev, elem, &command->content, free);
			if (elem && ft_strchr(")", ((char *)elem->content)[0]))
				fill_error(9);
		}
		else if (ft_strchr(")", ((char *)elem->content)[0]))
		{
			br_l += ++command->bracket_r;
			elem = ft_lst_delnext(prev, elem, &command->content, free);
			if (elem && ft_strchr("(", ((char *)elem->content)[0]))
				fill_error(9);
		}
		else
		{
			prev = elem;
			elem = elem->next;
		}
	}
}

static void	bracket_reduce(t_command *command)
{
	if (command->bracket_l > 0 && command->bracket_r > 0)
	{
		if (command->bracket_r > command->bracket_l)
		{
			command->bracket_r -= command->bracket_l;
			command->bracket_l = 0;
		}
		else
		{
			command->bracket_l -= command->bracket_r;
			command->bracket_r = 0;
		}
	}
}

void	parse_brackets(t_command *cmd)
{
	t_command	*command;
	int			br_r;
	int			br_l;

	br_l = 0;
	br_r = 0;
	command = cmd;
	while (command)
	{
		command->bracket_r = 0;
		command->bracket_l = 0;
		parse_bracket_tool(command, command->content, &br_l, &br_r);
		bracket_reduce(command);
		command = command->next;
	}
	if (br_l != br_r)
		fill_error(9);
}
