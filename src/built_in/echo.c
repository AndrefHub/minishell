/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:36:53 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/15 16:08:41 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_first(char *arg)
{
	int	counter;

	counter = 0;
	if (arg[counter] == '-')
	{
		while (arg[++counter])
			if (arg[counter] != 'n')
				return (0);
		return (1);
	}
	else
		return (0);
}

int	echo(char **argv)
{
	int	flag;

	flag = 1;
	if (check_first(argv[1]))
	{
		++argv;
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
	g_msh.last_ex_code = 0;
	return (1);
}

int	exit_too_many_args(void )
{
	ft_putstr_fd("exit: too many arguments\n", 2);
	g_msh.last_ex_code = 1;
	return (1);
}

int	msh_exit(char **argv)
{
	int	counter;

	ft_putendl_fd("exit", 2);
	if (ft_arraylen((void **)argv) < 3)
	{
		if (argv && argv[1])
		{
			counter = -1;
			if (argv[1][0] == '-' || argv[1][0] == '+')
				++counter;
			while (argv[1][++counter])
			{
				if (!ft_isdigit(argv[1][counter]))
				{
					ft_putstr_fd("exit: ", 2);
					ft_putstr_fd(argv[1], 2);
					ft_putendl_fd(": numeric argument required", 2);
					exit(255);
				}
			}
			exit(ft_atoi(argv[1]));
		}
		exit(g_msh.last_ex_code);
	}
	return (exit_too_many_args());
}
