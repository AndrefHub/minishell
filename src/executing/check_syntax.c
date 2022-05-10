/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:36:49 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/10 18:11:57 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_spops(char *str, int mode)
{
	int	i;

	i = mode;
	while (i != 9)
	{
		if (ft_find_substr(str, g_msh.sp_ops[i]))
			return (i);
		i++;
	}
	return (-1);
}
