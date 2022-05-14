/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:36:55 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/14 12:41:08 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int     ft_start_builtin(int (*f)(char **), char **argv)
{
	f(argv);
	return 1;
}

int check_for_built_in(char **args)
{
	int is_built_in;

	is_built_in = 0;
	if (ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
		is_built_in += ft_start_builtin(echo, args);
	else if (ft_strncmp(args[0], "env", ft_strlen(args[0])) == 0)
		is_built_in += ft_start_builtin(env, g_msh.envp);
	else if (ft_strncmp(args[0], "exit", ft_strlen(args[0])) == 0)
		exit(0);
	else if (ft_strncmp(args[0], "cd", ft_strlen(args[0])) == 0)
		is_built_in += ft_start_builtin(ft_chdir, g_msh.envp);
	return is_built_in;
}
