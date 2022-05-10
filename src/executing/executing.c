/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:36:46 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/10 17:56:56 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// int executor(char **args)
// {
// 	int		code;
// 	pid_t   pid;

// 	if (!check_for_built_in(args))
// 	{
// 		pid = fork();
// 		if (pid)
// 			waitpid(pid, NULL, 0);
// 		else
// 		{
// 			args[0] = find_binary(args[0], g_msh.envp);
// 			code = execve(args[0], args, g_msh.envp);
// 			if (code)
// 				return (errno);
// 		}
// 	}
// 	return (0);
// }
