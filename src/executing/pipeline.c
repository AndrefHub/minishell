/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 20:14:06 by lsherry           #+#    #+#             */
/*   Updated: 2022/05/15 16:20:54 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	get_error_code(int pid_fork)
{
	int	ret_code;

	if (pid_fork != 0)
		waitpid(pid_fork, &ret_code, 0);
	else
		ret_code = g_msh.last_ex_code << 8;
	return (ret_code);
}

t_command	*pipeline(t_command *to_pipe)
{
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
	set_error_code(get_error_code(pid_fork));
	return (to_pipe);
}
