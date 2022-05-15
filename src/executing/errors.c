/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 20:20:17 by lsherry           #+#    #+#             */
/*   Updated: 2022/05/15 11:41:01 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	reset_errors(void)
{
	g_msh.err_code = 0;
	g_msh.err_text = NULL;
}

void	set_error_code(int wpid_ret)
{
	int	code;

	code = wpid_ret >> 8 & 0xff;
	g_msh.last_ex_code = code;
}

int	fill_error(int code)
{
	if (code == 0)
		g_msh.err_text = ft_strdup("syntax error near unexpected token ';'");
	if (code == 1)
		g_msh.err_text = ft_strdup("syntax error near unexpected token '&&'");
	if (code == 2)
		g_msh.err_text = ft_strdup("syntax error near unexpected token '||'");
	if (code == 3)
		g_msh.err_text = ft_strdup("syntax error near unexpected token '|'");
	if (code == 4 || code == 5)
		g_msh.err_text = ft_strdup
			("syntax error near unexpected token '<<' or '<'");
	if (code == 6 || code == 7)
		g_msh.err_text = ft_strdup
			("syntax error near unexpected token '>>' or '>'");
	if (code == 9)
		g_msh.err_text = ft_strdup
			("syntax error near unexpected token '(' or ')'");
	g_msh.err_code = 258;
	return (0);
}

int	check_syntax(t_command *command)
{
	t_command	*copy;

	copy = command;
	while (copy)
	{
		if (!copy->content || !copy->content->content)
		{
			fill_error(copy->link_type);
			break ;
		}
		copy = copy->next;
	}
	if (g_msh.err_code != 0 || g_msh.err_text != NULL)
	{
		ft_putendl_fd(g_msh.err_text, 2);
		g_msh.last_ex_code = g_msh.err_code;
		return (0);
	}
	return (1);
}
