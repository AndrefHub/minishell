/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:36:51 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/14 13:51:43 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int env()
{
	t_list	*envp;

	envp = g_msh.envp;
	if (!envp)
		return (-1);
	while (envp)
	{
		ft_printf("%s=%s\n", envp_get_key(envp), envp_get_value(envp));
		envp = envp->next;
	}
	return (0);
}
