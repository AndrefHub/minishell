/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:12:18 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/14 17:20:05 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_entry_envp(t_envp *entry)
{
	free(((t_envp *)entry)->key);
	free(((t_envp *)entry)->value);
	free(entry);
}

void	set_entry_envp(t_envp *entry)
{
	t_list	*envp;

	envp = g_msh.envp;
	while (envp)
	{
		if (ft_strcmp(envp_get_key(envp), ((t_envp *)entry)->key) == 0)
		{
			if (((t_envp *)entry)->value[0])
			{
				free_entry_envp(envp->content);
				envp->content = entry;
			}
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
			set_entry_envp(entry);
		}
		update_cenvp();
	}
	else
		env();
	return (1);
}
