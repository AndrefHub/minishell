/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:36:55 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/14 20:58:16 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_start_builtin(int (*f)(char **), char **argv)
{
	f(argv);
	return (1);
}

int	check_for_built_in(char **args)
{
	if (ft_strncmp(args[0], "exit", ft_strlen(args[0])) == 0)
		return (msh_exit(args));
	if (ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
		return (echo(args));
	if (ft_strncmp(args[0], "env", ft_strlen(args[0])) == 0)
		return (env());
	if (ft_strncmp(args[0], "export", ft_strlen(args[0])) == 0)
		return (export(args));
	if (ft_strncmp(args[0], "unset", ft_strlen(args[0])) == 0)
		return (unset(args));
	if (ft_strncmp(args[0], "cd", ft_strlen(args[0])) == 0)
		return (ft_chdir(args[1]));
	if (ft_strncmp(args[0], "pwd", ft_strlen(args[0])) == 0)
		return (pwd());
	return (0);
}
