/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envparam.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:37:39 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/14 22:08:08 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	find_at_first(const char *string, char *pattern)
{
	int	i;
	int	len;

	i = 0;
	if (!pattern || !string)
		return (0);
	len = (int) ft_strlen(pattern);
	while (i < len)
	{
		if (string[i] != pattern[i])
			return (0);
		i++;
	}
	if (ft_strchr("=", string[i]))
		return (1);
	return (0);
}

char	*ft_find_envp(char *parameter)
{
	char	*out;
	t_list	*envp;

	envp = g_msh.envp;
	while (envp)
	{
		if (ft_strcmp(envp_get_key(envp), parameter) == 0)
		{
			out = ft_strdup(envp_get_value(envp));
			return (out);
		}
		envp = envp->next;
	}
	return (ft_strdup(""));
}

void	ft_increment_shlvl(void )
{
	t_list	*envp;
	char	*shlvl;
	int		lvl;

	envp = g_msh.envp;
	while (envp)
	{
		if (ft_strcmp(envp_get_key(envp), "SHLVL") == 0)
		{
			shlvl = envp_get_value(envp);
			lvl = ft_atoi(shlvl);
			free(shlvl);
			((t_envp *)envp->content)->value = ft_itoa(++lvl);
			return ;
		}
		envp = envp->next;
	}
}
