/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:36:46 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/15 19:05:22 by kdancy           ###   ########.fr       */
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
		return (0);
	pid_fork = fork();
	if (!pid_fork)
	{
		binary = find_binary(command[0]);
		if (!binary || !ft_strlen(binary))
			exit(0);
		if (!ft_strchr(binary, '/'))
			exit(command_not_found(binary));
		execve(binary, command, g_msh.cenvp);
		perror(binary);
		free(binary);
		exit(errno);
	}
	return (pid_fork);
}

static int	exe_tool(t_command *cmd)
{
	ft_com_rm_space(cmd);
	set_variables(cmd);
	ft_com_rm_quotes(cmd, "\"");
	ft_com_rm_quotes(cmd, "\'");
	parse_redirects(cmd);
	open_files(cmd);
	set_wildcards(cmd);
	if (!check_syntax(cmd))
		return (0);
	return (1);
}

static int	is_start(t_command *cmd, int prev_link_type, t_vector *br,
	t_vector *flag)
{
	if (cmd->bracket_l > 0 && ((prev_link_type == DOUBLE_AND
				&& g_msh.last_ex_code != 0)
			|| (prev_link_type == DOUBLE_OR && g_msh.last_ex_code == 0)))
	{
		flag->x = br->x;
		flag->y = 0;
	}
	else if (br->y == flag->x)
		flag->y = 1;
	return (0);
}

//br.x = prev_brackets;
//br.y = cur_brackets;
//flag.x = flag
//flag.y = start
int	execute_commands(t_command *cmd)
{
	int			prev_link_type;
	t_vector	br;
	t_vector	flag;

	flag.y = 1;
	br.y = 0;
	br.x = 0;
	prev_link_type = SEMICOLON;
	flag.x = -1;
	while (cmd)
	{
		if (!exe_tool(cmd))
			return (1);
		br.y += cmd->bracket_l;
		is_start(cmd, prev_link_type, &br, &flag);
		if (flag.y && ((prev_link_type == DOUBLE_AND && g_msh.last_ex_code == 0)
				|| (prev_link_type == DOUBLE_OR && g_msh.last_ex_code != 0)
				|| prev_link_type == SEMICOLON))
			cmd = pipeline(cmd);
		br.y -= cmd->bracket_r;
		br.x = br.y;
		prev_link_type = cmd->link_type;
		cmd = cmd->next;
	}
	return (0);
}
