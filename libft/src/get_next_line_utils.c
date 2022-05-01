/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andref <andref@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 10:56:57 by kdancy            #+#    #+#             */
/*   Updated: 2021/11/20 13:33:24 by andref           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

size_t	ft_strchr_i(const char *s, int c)
{
	size_t	fo;

	fo = 0;
	if (s)
		while (s[fo] && s[fo] != c)
			++fo;
	return (fo);
}

void	free_fd_buff(t_buff **head, int fd)
{
	t_buff	*fd_buffer;
	t_buff	*prev_buffer;

	prev_buffer = *head;
	fd_buffer = NULL;
	if (prev_buffer->fd == fd)
	{
		(*head) = (*head)->next;
		free(prev_buffer->buff);
		free(prev_buffer);
		return ;
	}
	while (prev_buffer->next)
	{
		if (prev_buffer->next->fd == fd)
		{
			fd_buffer = prev_buffer->next;
			prev_buffer->next = fd_buffer->next;
			free(fd_buffer->buff);
			free(fd_buffer);
			return ;
		}
		prev_buffer = prev_buffer->next;
	}
}
