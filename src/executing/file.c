/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 20:27:45 by lsherry           #+#    #+#             */
/*   Updated: 2022/05/14 20:27:46 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_file	*ft_file_new(char *filename, int link_type)
{
	t_file	*file;

	file = malloc(sizeof(*file));
	if (!file)
		return (NULL);
	file->f_name = ft_strdup(filename);
	file->fd = -1;
	file->mode = link_type;
	return (file);
}

//	Add error signal for multiple in/outfiles
void	set_file_in_command(t_command *command, int link_type, t_list *tmp)
{
	char	*filename;

	if (!tmp || !tmp->next || !tmp->next->content)
		filename = "";
	else
		filename = (char *) tmp->next->content;
	if ((link_type == HEREDOC || link_type == REDIR_IN))
	{
		if (command->infile == NULL)
			command->infile = ft_file_new(filename, link_type);
		else
			fill_error(link_type);
	}
	else if ((link_type == REDIR_OUT_AP || link_type == REDIR_OUT_TR))
	{
		if (command->outfile == NULL)
			command->outfile = ft_file_new(filename, link_type);
		else
			fill_error(link_type);
	}
}
