#include "../minishell.h"

int executor(char **args)
{
	int		code;
	pid_t   pid;

	// args[0] = find_binary(args[0], envp);
	if (!check_for_built_in(args))
	{
		pid = fork();
		if (pid)
		{
			waitpid(pid, NULL, 0);
		}
		else
		{
			args[0] = find_binary(args[0], g_msh.envp);
			code = execve(args[0], args, g_msh.envp);
			return (code);
		}
	}
	return (0);
}