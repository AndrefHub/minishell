/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:36:26 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/15 16:24:02 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
