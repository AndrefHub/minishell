#include "../../minishell.h"

char	*choose_dir(char *dir)
{
	char	*path;

	if (dir)
	{
		if (dir[0] == '/')
			path = ft_strdup(dir);
		else	
			path = ft_strcat_delim(ft_find_envp("PWD"), '/', dir);
	}
	else
		path = ft_find_envp("HOME");
	return (path);
}

int	ft_chdir()
{
	// int		code;
	// char	*path;

	// if (args[1])
	// {
	// 	if (args[1][0] == '/')
	// 		path = ft_strdup(args[1]);
	// 	else	
	// 		path = ft_strcat_delim(ft_find_envp("PWD"), '/', args[1]);
	// }
	// else
	// 	path = ft_find_envp("HOME");
	// if (!path)
	// 	return (228);
	// code = chdir(path);
	// if (!code)
	// 	g_msh.curr_dir = getcwd(path, 100);
	// free(path);
	// path = malloc(100);
	// getcwd(path, 100);
	// ft_putendl_fd(getcwd(path, 100), 2);
	update_cenvp();
	return (1);
}