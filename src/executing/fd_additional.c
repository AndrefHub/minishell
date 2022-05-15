/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_additional.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:54:44 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/15 16:03:50 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	dup2_and_close(int from, int to)
{
	dup2(from, to);
	close(from);
}

void	init_t_pipe_fd(t_pipe_fd *fd_data)
{
	fd_data->stdin_res = dup(0);
	fd_data->stdout_res = dup(1);
	fd_data->fd_in = dup(fd_data->stdin_res);
	fd_data->fd_out = 1;
}

void	reset_t_pipe_fd(t_pipe_fd *fd_data)
{
	dup2_and_close(fd_data->stdin_res, 0);
	dup2_and_close(fd_data->stdout_res, 1);
}
