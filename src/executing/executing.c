/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:36:46 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/11 11:49:42 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	execute(char **command)
{
	pid_t	pid_fork;
	char 	*binary;

	pid_fork = fork();
	if (!pid_fork) {
		binary = find_binary(command[0]);
		if (!binary || !ft_strlen(binary))
		{
			print_nothing(0);
			exit(0);
		}
		execve(binary, command, g_msh.envp);
		perror(binary);
		exit(errno);
	}
	return (pid_fork);
}

int	execute_commands(t_command *cmd)
{
	int			prev_link_type;

	prev_link_type = SEMICOLON;
	while (cmd)
	{
		if ((prev_link_type == DOUBLE_AND && g_msh.err_code == 0)
			|| (prev_link_type == DOUBLE_OR && g_msh.err_code != 0)
			|| prev_link_type == SEMICOLON)
		{
			cmd = pipeline(cmd);
		}
		prev_link_type = cmd->link_type;
		cmd = cmd->next;
	}
	return (0);
}
