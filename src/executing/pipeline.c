#include "../../minishell.h"

void	execute(char **command)
{
	// char	*binary;
	int		code;

	command[0] = find_binary(command[0], g_msh.envp);
	code = execve(command[0], command, g_msh.envp);
	// ft_putnbr_fd(code, 2);
	// ft_putendl_fd("", 2);
	// ft_freesplit(command);
	// if (code < 0)
	// 	ft_exit_message(binary, 2);
}

void	do_pipe(t_pipe_fd *fd_data)
{
	pipe(fd_data->pipe_fds);
	fd_data->fd_in = fd_data->pipe_fds[0];
	fd_data->fd_out = fd_data->pipe_fds[1];
}

void	dup2_and_close(int from, int to)
{
	dup2(from, to);
	close(from);
}

void	pipeline(t_command *to_pipe)
{
	t_command   *tmp;
	pid_t		pid_fork;
	t_pipe_fd	fd_data;

	// init fd_data
	fd_data.stdin_res = dup(0);
	fd_data.stdout_res = dup(1);
	fd_data.fd_in = dup(fd_data.stdin_res);
	// init fd_data end
	tmp = to_pipe;
	while (1)
	{
		dup2_and_close(fd_data.fd_in, 0);
		if (tmp->link_type != PIPELINE)
			fd_data.fd_out = fd_data.stdout_res;
		else
			do_pipe(&fd_data);
		dup2_and_close(fd_data.fd_out, 1);
		pid_fork = fork();
		if (!pid_fork) 
			execute(tmp->name_args);
		if (tmp->link_type != PIPELINE)
			break ;
		tmp = tmp->next;
	}
	dup2_and_close(fd_data.stdin_res, 0);
	dup2_and_close(fd_data.stdout_res, 1);
	waitpid(pid_fork, NULL, 0);
}
