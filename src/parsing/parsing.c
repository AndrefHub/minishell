/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:36:33 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/10 17:56:41 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find_binary(char *command)
{
	char	**path;
	char	*binary;
	int		counter;

	counter = -1;
	if (!command || !command[0] || ft_strchr(command, '/'))
		return (command);
	path = ft_split(ft_find_envp("PATH", g_msh.envp), ':');
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

char	*substitute_envp(char *input, char **envp)
{
	int		i;
	char	*subbed;

	i = -1;
	subbed = ft_strdup("");
	while (input[++i])
	{
		if (input[i] == '$' && input[i + 1])
		{
			subbed = ft_strjoin_gnl(subbed, ft_find_envp(ft_strndup(input + i
							+ 1, ft_strchr_num(input + i + 1, ' ')), envp));
			while (input[i + 1] && !is_in(input[i + 1], FT_SPACE))
				++i;
		}
		else if (((i > 0 && is_in(input[i - 1], FT_SPACE)) || i == 0)
			&& input[i] == '~')
			subbed = ft_strjoin_gnl(subbed, ft_find_envp("HOME", envp));
		else
			subbed = ft_strcat_delim(subbed, input[i], "");
	}
	return (subbed);
}
