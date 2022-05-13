/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andref <andref@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:36:26 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/13 17:32:34 by andref           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char    **parse_to_lines(char *input)
{
    return (ft_split_space(input, "\n")); // for now. Need to add '\' functionality
}

void	start_one_line(char *line)
{
	t_command	*full_cmd;
	t_command	*cmd;
	t_list		*lst;

	lst = parse_quotes(line);
	lst = parse_parentheses(lst);
	cmd = parse_special_characters(lst);
	free(line);
	full_cmd = cmd;
	init_sig_handler(child_sig_handler);
	while (cmd)
	{
//		set_variables(cmd); // before start process
		ft_com_rm_space(cmd);
		parse_redirects(cmd);
		open_files(cmd);
//		if (!check_syntax(cmd))
//			return ;

		// ft_print_lst(cmd->content);
		// ft_putendl_fd(g_msh.sp_ops[cmd->link_type], 1);
		cmd = cmd->next;
	}
	execute_commands(full_cmd);
	// pipeline(full_cmd);
	ft_comclear(&full_cmd);
}

void	start_cycle(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		start_one_line(lines[i]);
		i++;
	}
}

void	start(char *input)
{
	char	**commands;

	if (!input)
		exit(130);
	if (!ft_strlen(input))
	{
		print_nothing(0);
		return;
	}
	commands = parse_to_lines(input);
	if (!commands[1])
		start_one_line(commands[0]);
	// start_one_line(input);
	else
		start_cycle(commands);
	free(commands);
}

t_list	*parse_parentheses(t_list *quotes)
{
	split_by_pattern(&quotes, "(");
	split_by_pattern(&quotes, ")");
	return (quotes);
}
