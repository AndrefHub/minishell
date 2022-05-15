/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 20:14:06 by lsherry           #+#    #+#             */
/*   Updated: 2022/05/15 13:54:47 by kdancy           ###   ########.fr       */
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

void	do_pipe(t_pipe_fd *fd_data)
{
	pipe(fd_data->pipe_fds);
	fd_data->fd_in = fd_data->pipe_fds[0];
	fd_data->fd_out = fd_data->pipe_fds[1];
}

void	choose_output(t_command *to_pipe, t_pipe_fd *fd_data)
{
	if (is_file_open(to_pipe->outfile))
		fd_data->fd_out = to_pipe->outfile->fd;
	else if (to_pipe->link_type != PIPELINE)
		fd_data->fd_out = fd_data->stdout_res;
	else
		do_pipe(fd_data);
}

int	one_line_saver(t_command *to_pipe)
{
	return (to_pipe->link_type != PIPELINE || !to_pipe->next
		|| !to_pipe->next->content || !to_pipe->next->content->content);
}

t_command	*pipeline(t_command *to_pipe)
{
	int			ret_code = 0;
	pid_t		pid_fork;
	t_pipe_fd	fd_data;

	if (!to_pipe || !to_pipe->content)
		return (to_pipe);
	init_t_pipe_fd(&fd_data);
	while (1)
	{
		if (is_file_open(to_pipe->infile))
			dup2(to_pipe->infile->fd, fd_data.fd_in);
		dup2_and_close(fd_data.fd_in, 0);
		choose_output(to_pipe, &fd_data);
		dup2_and_close(fd_data.fd_out, 1);
		init_sig_handler(child_sig_handler);
		ft_list_to_char_ptr(to_pipe);
		pid_fork = execute(to_pipe->name_args);
		if (one_line_saver(to_pipe))
			break ;
		to_pipe = to_pipe->next;
	}
	reset_t_pipe_fd(&fd_data);
	if (pid_fork > 0)
		waitpid(pid_fork, &ret_code, 0);
	set_error_code(ret_code);
	return (to_pipe);
}
