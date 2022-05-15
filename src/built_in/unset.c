/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 17:14:44 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/15 16:09:24 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	unset_one(char *arg)
{
	t_list	*envp;
	t_list	*prev;

	prev = NULL;
	envp = g_msh.envp;
	while (envp)
	{
		if (ft_strcmp(envp_get_key(envp), arg) == 0)
		{
			ft_lst_delnext(prev, envp, &g_msh.envp, free_envp_entry);
			return (0);
		}
		prev = envp;
		envp = envp->next;
	}
	return (1);
}

int	unset(char **args)
{
	while (*(++args))
	{
		unset_one(*args);
	}
	update_cenvp();
	g_msh.last_ex_code = 0;
	return (1);
}
