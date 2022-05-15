/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andref <andref@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:36:46 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/15 10:27:05 by andref           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	command_not_found(char *binary)
{
	g_msh.last_ex_code = 127;
	ft_putstr_fd(binary, 2);
	free(binary);
	ft_putendl_fd(": command not found", 2);
	return (g_msh.last_ex_code);
}

int	execute(char **command)
{
	pid_t	pid_fork;
	char	*binary;

	if (check_for_built_in(command))
	{
		// write(1, "built-in\n", 9);
		return (0);
	}
	pid_fork = fork();
	if (!pid_fork)
	{
		binary = find_binary(command[0]);
		if (!binary || !ft_strlen(binary))
			exit(0);
		// if (!ft_strchr(binary, '/'))
		// 	exit(command_not_found(binary));
		execve(binary, command, g_msh.cenvp);
		perror(binary);
		free(binary);
		exit(errno);
	}
	return (pid_fork);
}

int	execute_commands(t_command *cmd)
{
	int			prev_link_type;
	int			prev_brackets;
	int			cur_brackets;
	int			flag;
	int			start;

	start = 1;
	cur_brackets = 0;
	prev_brackets = 0;
	prev_link_type = SEMICOLON;
	flag = -1;
	while (cmd)
	{
		set_variables(cmd);
		set_wildcards(cmd);
		cur_brackets += cmd->bracket_l;
		if (cmd->bracket_l > 0 && ((prev_link_type == DOUBLE_AND
					&& g_msh.last_ex_code != 0)
				|| (prev_link_type == DOUBLE_OR && g_msh.last_ex_code == 0)))
		{
			flag = prev_brackets;
			start = 0;
		}
		else if (cur_brackets == flag)
			start = 1;
		if (start && ((prev_link_type == DOUBLE_AND && g_msh.last_ex_code == 0)
				|| (prev_link_type == DOUBLE_OR && g_msh.last_ex_code != 0)
				|| prev_link_type == SEMICOLON))
			cmd = pipeline(cmd);
		cur_brackets -= cmd->bracket_r;
		prev_brackets = cur_brackets;
		prev_link_type = cmd->link_type;
		cmd = cmd->next;
	}
	return (0);
}
