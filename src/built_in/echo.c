/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:36:53 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/14 14:56:09 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int echo(char **argv)
{
	int flag;

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

int msh_exit(char **argv)
{
	(void)argv;
	exit(0);

}
