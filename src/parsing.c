#include "../minishell.h"

char	**get_path(char **envp)
{
	char	**path;
	int		counter;

	path = NULL;
	counter = 0;
	while (envp[counter])
	{
		if (ft_strncmp(envp[counter], "PATH=", 5) == 0)
		{
			path = ft_split(envp[counter] + 5, ':');
			break ;
		}
		++counter;
	}
	return (path);
}

// char	**get_var_from_envp(char **envp, char *var)
// {
// 	char	**path;
// 	int		counter;

// 	path = NULL;
// 	counter = 0;
// 	while (envp[counter])
// 	{
// 		if (ft_strncmp(envp[counter], "PATH=", 5) == 0)
// 		{
// 			path = ft_split(envp[counter] + 5, ':');
// 			break ;
// 		}
// 		++counter;
// 	}
// 	return (path);
// }

char	*find_binary(char *command, char **envp)
{
	char	**path;
	char	*binary;
	int		counter;

	counter = -1;
	if (ft_strchr(command, '/'))
		return (command);
	path = get_path(envp);
	while (path[++counter])
	{
		binary = ft_strcat_delim(path[counter], '/', command);
		if (access(binary, X_OK) == 0)
		{
			ft_freesplit(path);
			return (binary);
		}
		free(binary);
	}
	ft_freesplit(path);
	return (ft_strdup(command));
}

char	**parser(char *input, char **envp)
{
	char	**args;
	// char	*binary;
	// int		code;

	args = ft_split_space(input);
	args[0] = find_binary(args[0], envp);
	return args;
	// code = execve(args[0], args, NULL);
	// ft_freesplit(args);
	// if (code < 0)
	// 	ft_exit_message(binary, 2);
}
