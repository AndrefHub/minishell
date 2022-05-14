#include "../../minishell.h"

int	ft_chdir(char **args)
{
	int		code;
	char	*path;

	if (args[1])
		path = args[1];
	else
		path = ft_find_envp("HOME", g_msh.envp);
	if (!path)
		return (228);
	code = chdir(path);
	if (!code)
		g_msh.pwd = ft_find_envp("PWD", g_msh.envp);
	return (1);
}