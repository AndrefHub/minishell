#include "../minishell.h"

int check_for_built_in(char **args)
{
	if (ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
	{
		pid_t	pid;

		pid = fork();
		if (pid)
		{
			waitpid(pid, NULL, 0);
		}
		else
		{
			echo(args);
		}
		return 1;
	}
	return 0;
}