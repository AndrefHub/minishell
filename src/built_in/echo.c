/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:36:53 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/14 20:01:54 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	echo(char **argv)
{
	int	flag;

	flag = 1;
	if (find_at_first(argv[1], "-n"))
	{
		argv++;
		flag = 0;
	}
	while (*++argv)
	{
		ft_printf("%s", *argv);
		if (*(argv + 1))
			ft_printf(" ");
	}
	if (flag)
		printf("\n");
	return (1);
}

int	msh_exit(char **argv)
{
	int	counter;

	ft_putendl_fd("exit", 2);
	if (argv && argv[1])
	{
		counter = -1;
		while (argv[1][++counter])
		{
			if (!ft_isdigit(argv[1][counter]))
			{
				ft_putstr_fd("msh: ", 2);
				ft_putstr_fd("exit: ", 2);
				ft_putstr_fd(argv[1], 2);
				ft_putendl_fd(": numeric argument required", 2);
				exit(255);
			}
		}
		exit(ft_atoi(argv[1]));
	}
	exit(g_msh.last_ex_code);
	return (1);
}
