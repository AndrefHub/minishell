/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 20:18:06 by lsherry           #+#    #+#             */
/*   Updated: 2022/05/14 20:18:07 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	heredoc(char *delim)
{
	char	*input;
	int		herepipe[2];

	pipe(herepipe);
	while (1)
	{
		input = readline("HEREDOC> ");
		if (!input)
			break ;
		if (ft_strlen(input) != 0
			&& ft_strncmp(delim, input, ft_strlen(input)) == 0)
		{
			free(input);
			break ;
		}
		ft_putstr_fd(input, herepipe[1]);
		ft_putchar_fd('\n', herepipe[1]);
		free(input);
	}
	close(herepipe[1]);
	return (herepipe[0]);
}
