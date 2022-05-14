/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:36:26 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/11 19:50:27 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**parse_to_lines(char *input)
{
	return (ft_split(input, '\n'));
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
	parse_brackets(cmd);
	while (cmd)
	{
		ft_com_rm_space(cmd);
		parse_redirects(cmd);
		open_files(cmd);
		if (!check_syntax(cmd))
			return ;
		ft_print_lst(cmd->content);
		printf("(: %d\n", cmd->bracket_l);
		printf("): %d\n", cmd->bracket_r);
		cmd = cmd->next;
	}
	execute_commands(full_cmd);
}

/*
 * ft_print_lst(cmd->content);
 * printf("(: %d\n", cmd->bracket_l);
 * printf("): %d\n", cmd->bracket_r);
 * */

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
		return ;
	}
	commands = parse_to_lines(input);
	if (!commands[1])
		start_one_line(commands[0]);
	else
		start_cycle(commands);
}
