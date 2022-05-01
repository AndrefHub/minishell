/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 10:56:41 by kdancy            #+#    #+#             */
/*   Updated: 2021/10/17 10:56:45 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_buff	*ft_buff_new(int fd)
{
	t_buff			*tmp;

	tmp = malloc(sizeof(t_buff));
	if (tmp)
	{
		tmp->buff = NULL;
		tmp->fd = fd;
		tmp->length = 0;
		tmp->bytes_read = 0;
		tmp->next = NULL;
	}
	return (tmp);
}

t_buff	*ft_buff_fd(int fd, t_buff **buff)
{
	t_buff			*tmp;

	if (!buff)
		return (NULL);
	if (!(*buff))
		(*buff) = ft_buff_new(fd);
	tmp = *buff;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		if (!(tmp->next))
		{
			tmp->next = ft_buff_new(fd);
			return (tmp->next);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_readnew(t_buff **fd_buffer)
{
	char	*new_buffer;
	char	*read_buffer;
	size_t	counter;

	new_buffer = malloc((*fd_buffer)->length + BUFFER_SIZE + 1);
	if (!new_buffer)
		return ;
	read_buffer = malloc(BUFFER_SIZE + 1);
	if (!read_buffer)
		free(new_buffer);
	if (!read_buffer)
		return ;
	counter = -1;
	if ((*fd_buffer)->buff)
		while (++counter < (*fd_buffer)->length)
			new_buffer[counter] = (*fd_buffer)->buff[counter];
	(*fd_buffer)->bytes_read = read((*fd_buffer)->fd, read_buffer, BUFFER_SIZE);
	counter = -1;
	while (++counter < (size_t)((*fd_buffer)->bytes_read))
		new_buffer[(*fd_buffer)->length + counter] = read_buffer[counter];
	new_buffer[(*fd_buffer)->length + counter] = '\0';
	free((*fd_buffer)->buff);
	free(read_buffer);
	(*fd_buffer)->buff = new_buffer;
	(*fd_buffer)->length = ft_strlen((*fd_buffer)->buff);
}

char	*realloc_end(t_buff **fd_buffer, size_t new_begin)
{
	char	*line;
	char	*buff;
	size_t	counter;

	buff = malloc((*fd_buffer)->length - new_begin + 1);
	line = malloc(new_begin + 1);
	if (!line || !buff)
	{
		free(buff);
		free(line);
		return (NULL);
	}
	counter = -1;
	while (++counter < new_begin)
		line[counter] = (*fd_buffer)->buff[counter];
	line[counter] = '\0';
	counter = -1;
	while (new_begin + ++counter < (*fd_buffer)->length)
		buff[counter] = (*fd_buffer)->buff[new_begin + counter];
	buff[counter] = '\0';
	free((*fd_buffer)->buff);
	(*fd_buffer)->buff = buff;
	(*fd_buffer)->length = ft_strlen(buff);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_buff	*buff;
	t_buff			*fd_buffer;
	char			*why;

	why = NULL;
	if (fd < 0 || read(fd, why, 0) < 0)
		return (NULL);
	fd_buffer = ft_buff_fd(fd, &buff);
	if (fd_buffer->length == 0)
	{
		ft_readnew(&fd_buffer);
		if (fd_buffer->bytes_read == 0)
			free_fd_buff(&buff, fd);
		if (fd_buffer->bytes_read <= 0)
			return (NULL);
	}
	while (ft_strchr_i(fd_buffer->buff, '\n') == fd_buffer->length
		&& fd_buffer->bytes_read != 0)
		ft_readnew(&fd_buffer);
	why = (realloc_end(&fd_buffer, ft_strchr_i(fd_buffer->buff, '\n') + 1));
	if (fd_buffer->length == 0 && fd_buffer->bytes_read < BUFFER_SIZE)
		free_fd_buff(&buff, fd);
	return (why);
}
