/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:03:54 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/15 22:24:16 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	open_infile(t_file *file)
{
	if (file)
	{
		if (file->mode == REDIR_IN)
			file->fd = open(file->f_name, O_RDONLY);
		else if (file->mode == HEREDOC)
			file->fd = heredoc(file->f_name);
	}
}

void	open_outfile(t_file *file)
{
	if (file)
	{
		if (file->mode == REDIR_OUT_AP)
			file->fd = open(file->f_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (file->mode == REDIR_OUT_TR)
			file->fd = open(file->f_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
}

int	is_file_open(t_file *file)
{
	if (file == NULL)
		return (0);
	if (REDIR_IN <= file->mode && file->mode <= REDIR_OUT_TR)
		return (file->fd > -1);
	if (file->mode == HEREDOC)
		return (file->f_name != NULL);
	return (0);
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

void	ft_free_file(t_file *file, int err)
{
	if (file)
	{
		if (err)
			close(file->fd);
		free(file->f_name);
		free(file);
	}
}
