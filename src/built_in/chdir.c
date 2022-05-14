#include "../../minishell.h"

void	ft_chdir(char **path)
{
	int	code;

	code = chdir(*path);
	if (!code)
		g_msh.pwd = ft_find_envp("PWD", g_msh.envp);
}