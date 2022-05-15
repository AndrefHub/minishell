/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:36:26 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/15 14:52:08 by kdancy           ###   ########.fr       */
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
	parse_brackets(cmd);
	while (cmd)
	{
		ft_com_rm_space(cmd);
		parse_redirects(cmd);
		open_files(cmd);
		if (!check_syntax(cmd))
			return ;
		cmd = cmd->next;
	}
	init_sig_handler(child_sig_handler);
	execute_commands(full_cmd);
	ft_comclear(&full_cmd, 0);
	init_sig_handler(parent_sig_handler);
}

void	check_end_and_start_one_line(char *line)
{
	int counter;

	counter = ft_strlen(line);
	while (line[--counter])
	{
		if (!ft_strchr("\t ", line[counter]))
		{
			if (ft_strchr("><|&;", line[counter]))
			{
				free(line);
				return ;
			}
			else
				break ;
		}
	}
	start_one_line(line);
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
		check_end_and_start_one_line(lines[i]);
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
		check_end_and_start_one_line(commands[0]);
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
