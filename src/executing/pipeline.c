#include "../../minishell.h"

void	execute(char **command)
{
	char	*binary;
	int		code;

	commamd[0] = find_binary(command[0], g_msh.envp);
	code = execve(command[0], command, g_msh.envp);
	// ft_freesplit(command);
	if (code < 0)
		ft_exit_message(binary, 2);
}

void    pipeline(t_command *to_pipe)
{
	t_command   *tmp;
	pid_t		pid;
	int			fd[2];

	tmp = to_pipe;
	while (tmp->link_type == PIPELINE)
	{
		pipe(fd);
		pid = fork();
		if (pid) 
		{
			close(fd[1]);
			dup2(fd[0], 0);
			if (tmp->next->link_type != PIPELINE)
				waitpid(pid, NULL, 0);
		}
		else
		{
			close(fd[0]);
			dup2(fd[1], 1);
			execute(tmp->name_args);
		}
	}
}