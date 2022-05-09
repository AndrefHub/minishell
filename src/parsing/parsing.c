#include "../../minishell.h"

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
	if (!command || !command[0] || ft_strchr(command, '/'))
		return (command);
	path = get_path(envp);
	while (path[++counter])
	{
		binary = ft_strcat_delim(path[counter], '/', ``);
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

char	*substitute_envp(char *input, char **envp)
{
	int		i;
	char    *subbed;

	i = -1;
	subbed = ft_strdup("");
	while (input[++i])
	{
		if (input[i] == '$' && input[i + 1])
		{
			subbed = ft_strjoin_gnl(subbed, ft_find_envp(ft_strndup(input + i + 1, ft_strchr_num(input + i + 1, ' ')), envp));
			while (input[i + 1] && !is_in(input[i + 1], FT_SPACE))
				++i;
		}
		else if (((i > 0 && is_in(input[i - 1], FT_SPACE)) || i == 0) && input[i] == '~')
		{
			subbed = ft_strjoin_gnl(subbed, ft_find_envp("HOME", envp));
			// ++i;
		}
		else
			subbed = ft_strcat_delim(subbed, input[i], ""); // <<< not really good, might change if feeling good 
	}
	// free(input); << not needed since we change free it in 
	return (subbed);
}

char	**parser_old(char *input, char **envp)
{
	char	**args;
	// int		code;

	input = substitute_envp(input, envp);
	args = ft_split_space(input, FT_SPACE);
	free(input);
	// if (!check_for_built_in(args))
	// 	code = execve(args[0], args, NULL);
	return args;
	
	// ft_freesplit(args);
	// if (code < 0)
	// 	ft_exit_message(binary, 2);
}
