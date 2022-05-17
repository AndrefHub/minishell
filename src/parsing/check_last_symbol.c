/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_last_symbol.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 16:10:28 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/15 20:10:29 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ftsj(const char *s1, const char *s2)
{
	return (ft_strjoin(s1, s2));
}

char	**parse_to_lines(char *input)
{
	return (ft_split(input, '\n'));
}

void	start_one_line(char *line)
{
	t_command	*full_cmd;
	t_command	*cmd;
	t_list		*lst;

	lst = parse_quotes(line);
	lst = parse_parentheses(lst);
	cmd = parse_special_characters(lst);
	free(line);
	full_cmd = cmd;
	if (!full_cmd)
		return ;
	init_sig_handler(child_sig_handler);
	parse_brackets(cmd);
	execute_commands(full_cmd);
	ft_comclear(&full_cmd, 0);
}

int	choose_code(char *spop, int mode)
{
	if (spop[1 - mode] == ';')
		return (SEMICOLON);
	if (spop[1 - mode] == '>')
		return (REDIR_OUT_AP);
	if (spop[1 - mode] == '<')
		return (REDIR_IN);
	if (spop[1 - mode] == '&')
		return (DOUBLE_AND);
	if (spop[1 - mode] == '|' && spop[0 + mode] == '|')
		return (DOUBLE_OR);
	return (PIPELINE);
}

void	check_begin_and_start_one_line(char *line)
{
	int	counter;

	counter = -1;
	while (line[++counter])
	{
		if (!ft_strchr("\t ", line[counter]))
		{
			if (ft_strchr("><|&;", line[counter]))
			{
				fill_error(choose_code(line + counter, 1));
				free(line);
				check_syntax(NULL);
				return ;
			}
			else
				break ;
		}
	}
	start_one_line(line);
}
