/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:36:42 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/14 15:59:13 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_msh	g_msh;

void	ft_args_usage(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
}

char	**make_sp_ops(void )
{
	char	**lst;

	lst = malloc(sizeof(*lst) * (ENDING_TYPE + 1));
	lst[0] = ft_strdup(";");
	lst[1] = ft_strdup("&&");
	lst[2] = ft_strdup("||");
	lst[3] = ft_strdup("|");
	lst[4] = ft_strdup("<<");
	lst[5] = ft_strdup("<");
	lst[6] = ft_strdup(">>");
	lst[7] = ft_strdup(">");
	lst[8] = NULL;
	return (lst);
}

void	set_g_msh(char **envp)
{
	g_msh.envp = parse_envp(envp);
	g_msh.cenvp = NULL;
	update_cenvp();
	g_msh.sp_ops = make_sp_ops();
	g_msh.last_ex_code = 0;
	g_msh.pwd = ft_find_envp("PWD");
}

int	ft_is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;

	ft_args_usage(argc, argv, envp);
	set_g_msh(envp);
	setup_term();
	while (1)
	{
		reset_errors();
		init_sig_handler(parent_sig_handler);
		input = readline(MINISHELLNAME);
		if (input && input[0] && !ft_is_empty(input))
			add_history(input);
		start(input);
		free(input);
	}
	return (0);
}
