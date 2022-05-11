/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:03:54 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/11 18:01:49 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*heredoc(char *delim)
{
	char	*full_input;
	char	*input;
	char	*tmp;

	full_input = ft_strdup("");
	while (1)
	{
		input = readline("HEREDOC> ");
		if (!input)
			return (full_input);
		if (ft_strlen(input) != 0 && ft_strncmp(delim, input, ft_strlen(input)) == 0)
		{
			free(input);
			return (full_input);
		}
		tmp = ft_strcat_delim(full_input, '\n', input);
		free(full_input);
		free(input);
		full_input = tmp;
	}
	return (full_input);
}

void	open_infile(t_file *file)
{
	char	*heredoc_res;

	if (file)
	{
		if (file->mode == REDIR_IN)
			file->fd = open(file->f_name, O_RDONLY);
		else if (file->mode == HEREDOC)
		{
			heredoc_res = heredoc(file->f_name);
			free(file->f_name);
			file->f_name = heredoc_res;
		}
	}
}

void	open_outfile(t_file *file)
{
	if (file)
	{
		if (file->mode == REDIR_OUT_AP)
			file->fd = open(file->f_name, O_WRONLY | O_CREAT | O_APPEND);
		else if (file->mode == REDIR_OUT_TR)
			file->fd = open(file->f_name, O_WRONLY | O_CREAT | O_TRUNC);
	}
}

int	is_file_open(t_file *file)
{
	if (REDIR_IN <= file->mode && file->mode <= REDIR_OUT_TR)
		return (file->fd > -1);
	if (file->mode == HEREDOC)
		return (file->f_name);
}

void	open_files(t_command *command)
{
	while (command)
	{
		open_infile(command->infile);
		open_outfile(command->outfile);
		command = command->next;
	}    
}