#include "../minishell.h"

int check_for_built_in(char **args, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid)
	{
		waitpid(pid, NULL, 0);
	}
	else
	{
		if (ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
		{
			echo(args);
			return 1;
		}
		else
		{
			int code;
			args[0] = find_binary(args[0], envp);
			code = execve(args[0], args, envp);
			if (code)
				printf("Error: code %d", code);
		}
	}
	return 0;
}