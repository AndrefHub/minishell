/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:12:18 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/15 19:36:02 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_envp_entry(void *entry)
{
	free(((t_envp *)entry)->key);
	free(((t_envp *)entry)->value);
	free(entry);
}

void	set_envp_entry(t_envp *entry)
{
	t_list	*envp;

	envp = g_msh.envp;
	while (envp)
	{
		if (ft_strcmp(envp_get_key(envp), ((t_envp *)entry)->key) == 0)
		{
			if (((t_envp *)entry)->value[0])
			{
				free_envp_entry(envp->content);
				envp->content = entry;
			}
			else
				free_envp_entry(entry);
			return ;
		}
		envp = envp->next;
	}
	ft_lstadd_back(&(g_msh.envp), ft_lstnew(entry));
}

int	export(char **args)
{
	t_envp	*entry;

	if (args[1])
	{
		while (*(++args))
		{
			entry = make_envp_entry(*args);
			set_envp_entry(entry);
		}
		update_cenvp();
	}
	else
		env();
	g_msh.last_ex_code = 0;
	return (1);
}
