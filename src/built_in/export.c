/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andref <andref@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:12:18 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/14 16:29:37 by andref           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// int update_env(char *arg)
// {
	
// }

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

int export(char **args)
{
	t_envp	*entry;
	
	while (*(++args))
	{
		entry = make_envp_entry(*args);
		set_entry_envp(entry);
	}
	update_cenvp();
	return (1);
}