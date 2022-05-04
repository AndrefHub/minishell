#include "../../minishell.h"

int executor(char **args)
{
	int		code;
	pid_t   pid;

	if (!check_for_built_in(args))
	{
		pid = fork();
		if (pid)
			waitpid(pid, NULL, 0);
		else
		{
			args[0] = find_binary(args[0], g_msh.envp);
			code = execve(args[0], args, g_msh.envp);
			if (code)
				return (errno);
		}
	}
	return (0);
}