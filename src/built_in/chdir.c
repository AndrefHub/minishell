/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 15:53:40 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/15 16:08:32 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_envp	*make_pwd(char *key, char *value)
{
	t_envp	*pwd;

	pwd = malloc(sizeof(*pwd));
	pwd->key = ft_strdup(key);
	pwd->value = ft_strdup(value);
	return (pwd);
}

int	ft_chdir(char *dir)
{
	if (dir == NULL || ft_strcmp(dir, "~") == 0)
		dir = ft_find_envp("HOME");
	else
		dir = ft_strdup(dir);
	if (chdir(dir) == 0)
	{
		set_envp_entry(make_pwd("OLDPWD", g_msh.pwd));
		free(g_msh.pwd);
		g_msh.pwd = getcwd(NULL, 0);
		set_envp_entry(make_pwd("PWD", g_msh.pwd));
		g_msh.last_ex_code = 0;
	}
	else
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(strerror(2), 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(dir, 2);
		g_msh.last_ex_code = 2;
	}
	free(dir);
	update_cenvp();
	return (1);
}
