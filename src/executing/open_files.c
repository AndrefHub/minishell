/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andref <andref@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:03:54 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/12 00:34:37 by andref           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
////	int fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_APPEND, 0666);
int	heredoc(char *delim)
{
	// char	*full_input;
	char	*input;
	// char	*tmp;
	int		herepipe[2];

	pipe(herepipe);
	// close(herepipe[1]);
	// full_input = ft_strdup("");
	while (1)
	{
		input = readline("HEREDOC> ");
		if (!input)
			break ;//(full_input);
		if (ft_strlen(input) != 0 && ft_strncmp(delim, input, ft_strlen(input)) == 0)
		{
			free(input);
			break ;//(full_input);
		}
		// tmp = ft_strcat_delim(full_input, '\n', input);
		ft_putstr_fd(input, herepipe[1]);
		ft_putchar_fd('\n', herepipe[1]);
		// free(full_input);
		free(input);
		// full_input = tmp;
	}
	close(herepipe[1]);
	return herepipe[0];
	// return (full_input);
}

// char	*heredoc(char *delim)
// {
// 	char	*input;
// 	int fd = open(".heredoc_tmp", O_RDWR | O_CREAT | O_TRUNC, 0666);

// 	// close(herepipe[1]);
// 	// full_input = ft_strdup("");
// 	while (1)
// 	{
// 		input = readline("HEREDOC> ");
// 		if (!input)
// 			break ;//(full_input);
// 		if (ft_strlen(input) != 0 && ft_strncmp(delim, input, ft_strlen(input)) == 0)
// 		{
// 			free(input);
// 			break ;//(full_input);
// 		}
// 		// tmp = ft_strcat_delim(full_input, '\n', input);
// 		ft_putstr_fd(input, fd);
// 		ft_putchar_fd('\n', fd);
// 		// free(full_input);
// 		free(input);
// 		// full_input = tmp;
// 	}
// 	close(fd);
// 	return ".heredoc_tmp";
// 	// return (full_input);
// }

void	open_infile(t_file *file)
{
	// char	*heredoc_res;

	if (file)
	{
		if (file->mode == REDIR_IN)
			file->fd = open(file->f_name, O_RDONLY);
		else if (file->mode == HEREDOC)
		{
			file->fd = heredoc(file->f_name);;
			// file->f_name = heredoc(file->f_name);
			// file->fd = open(file->f_name, O_RDONLY);
			// heredoc_res = heredoc(file->f_name);
			// free(file->f_name);
			// file->f_name = heredoc_res;
		}
	}
}

void	open_outfile(t_file *file)
{
	if (file)
	{
		if (file->mode == REDIR_OUT_AP)
			file->fd = open(file->f_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (file->mode == REDIR_OUT_TR)
			file->fd = open(file->f_name, O_WRONLY | O_CREAT | O_TRUNC, 0b110100100);
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
