#include "../minishell.h"

int     ft_start_builtin(int (*f)(char **), char **argv)
{
	pid_t   pid;

	pid = fork();
	if (pid)
	{
		waitpid(pid, NULL, 0);
	}
	else
		f(argv);
	return 1;
}

int check_for_built_in(char **args)
{
	int is_built_in;

	is_built_in = 0;
	if (ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
		is_built_in += ft_start_builtin(echo, args);
	if (ft_strncmp(args[0], "env", ft_strlen(args[0])) == 0)
		is_built_in += ft_start_builtin(env, g_msh.envp);
	return is_built_in;
}
