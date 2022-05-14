/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:36:55 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/14 14:50:53 by kdancy           ###   ########.fr       */
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
		is_built_in += echo(args);
	else if (ft_strncmp(args[0], "env", ft_strlen(args[0])) == 0)
		is_built_in += env();
	else if (ft_strncmp(args[0], "export", ft_strlen(args[0])) == 0)
		is_built_in += export(args);
	else if (ft_strncmp(args[0], "exit", ft_strlen(args[0])) == 0)
		exit(g_msh.err_code);
	else if (ft_strncmp(args[0], "cd", ft_strlen(args[0])) == 0)
		is_built_in += ft_chdir();
	return is_built_in;
}
