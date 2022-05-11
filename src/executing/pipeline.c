#include "../../minishell.h"

void	parent_sig_handler(int sigsum, siginfo_t *sig, void *context)
{
	if (sigsum == SIGINT)
		clear_term_signal();
	else if (sigsum == SIGQUIT)
	{
		print_nothing();
		write(2, "  \r", 3);
		write(2, MINISHELLNAME, ft_strlen(MINISHELLNAME));
	}
	(void ) sig;
	(void ) context;
}
//
//void	child_sig_handler(int sigsum, siginfo_t *sig, void *context)
//{
//
//}

void	clear_term_signal(void )
{
	print_nothing();
	write(2, "  \n", 3);
	rl_replace_line("", 0);
	print_nothing();
}

void	print_nothing(void )
{
	rl_on_new_line();
	rl_redisplay();
}

void	init_sig_handler(void (*handler) (int, siginfo_t *, void *))
{
	struct sigaction sigact;

	sigact.sa_flags = SA_SIGINFO;
	sigact.sa_sigaction = handler;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = 0;
	sigaction(SIGINT, &sigact, NULL); //Ctrl + C
// 	sigaction(SIGTERM, &sigact, NULL); //
	sigaction(SIGQUIT, &sigact, NULL); //Ctrl +

}

int	execute(char **command)
{
	pid_t pid_fork;
	pid_fork = fork();

	if (!pid_fork) {
		command[0] = find_binary(command[0]);
		execve(command[0], command, g_msh.envp);
		perror(command[0]);
		exit(errno);
	}

	return (pid_fork);
}

void	init_t_pipe_fd(t_pipe_fd *fd_data)
{
	fd_data->stdin_res = dup(0);
	fd_data->stdout_res = dup(1);
	fd_data->fd_in = dup(fd_data->stdin_res);
	fd_data->fd_out = 1;
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

void	set_error_code(int wpid_ret)
{
	int	code;
	
	code = WEXITSTATUS(wpid_ret);
	g_msh.err_code = code;
}

t_command	*pipeline(t_command *to_pipe)
{
	int			ret_code;
	pid_t		pid_fork;
	t_pipe_fd	fd_data;

	if (!to_pipe)
		return (NULL);
	init_t_pipe_fd(&fd_data);
	while (1)
	{
		dup2_and_close(fd_data.fd_in, 0);
		if (to_pipe->link_type != PIPELINE)
			fd_data.fd_out = fd_data.stdout_res;
		else
			do_pipe(&fd_data);
		dup2_and_close(fd_data.fd_out, 1);
		pid_fork = execute(to_pipe->name_args);
		if (to_pipe->link_type != PIPELINE)
			break ;
		to_pipe = to_pipe->next;
	}
	dup2_and_close(fd_data.stdin_res, 0);
	dup2_and_close(fd_data.stdout_res, 1);
	waitpid(pid_fork, &ret_code, 0);
	set_error_code(ret_code);
	return (to_pipe);
}
