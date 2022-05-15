/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andref <andref@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:36:26 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/15 10:25:03 by andref           ###   ########.fr       */
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
	if (!full_cmd)
		return ;
	init_sig_handler(child_sig_handler);
	parse_brackets(cmd);
//	while (cmd)
//	{
//
//		cmd = cmd->next;
//	}
	execute_commands(full_cmd);
	ft_comclear(&full_cmd, 0);
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
	{
		write(2, "exit\n", 5);
		exit(130);
	}
	else if (!ft_strlen(input))
	{
		print_nothing(0);
		return ;
	}
	commands = parse_to_lines(input);
	if (!commands[1])
		start_one_line(commands[0]);
	else
		start_cycle(commands);
	free(commands);
}

char	*find_binary(char *command)
{
	char	**path;
	char	*binary;
	int		counter;
	char	*envpath;

	counter = -1;
	if (!command || !command[0] || ft_strchr(command, '/'))
		return (command);
	envpath = ft_find_envp("PATH");
	path = ft_split(envpath, ':');
	free(envpath);
	while (path[++counter])
	{
		binary = ft_strcat_delim(path[counter], '/', command);
		if (access(binary, X_OK) == 0)
		{
			ft_freesplit(path);
			return (binary);
		}
		free(binary);
	}
	ft_freesplit(path);
	return (ft_strdup(command));
}
