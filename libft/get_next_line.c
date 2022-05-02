/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:55:43 by lsherry           #+#    #+#             */
/*   Updated: 2021/11/16 17:19:17 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strnew(size_t size)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	str[size] = 0;
	while (size-- != 0)
		str[size] = 0;
	return (str);
}

static char	*rem_checker(char **rem, char **str)
{
	char	*p_n;
	char	*tmp;

	p_n = NULL;
	if (*rem)
	{
		p_n = ft_strchr(*rem, '\n');
		if (p_n)
		{
			tmp = *rem;
			*rem = ft_strdup(p_n + 1);
			*(p_n + 1) = 0;
			*str = ft_strdup(tmp);
			free(tmp);
		}
		else
		{
			*str = ft_strdup(*rem);
			free(*rem);
			*rem = NULL;
		}
	}
	else
		*str = ft_strnew(0);
	return (p_n);
}

char	*get_next_line(int fd)
{
	char			buffer[BUFFER_SIZE + 1];
	char			*p_n;
	char			*str;
	static char		*rem;
	int				rd;

	p_n = rem_checker(&rem, &str);
	while (!p_n)
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd <= 0)
			break ;
		buffer[rd] = 0;
		p_n = ft_strchr(buffer, '\n');
		if (p_n)
		{
			rem = ft_strdup(p_n + 1);
			*(p_n + 1) = 0;
		}
		str = ft_strjoin_gnl(str, buffer);
	}
	if (rd > 0 || ft_strlen(str) != 0 || rem != NULL)
		return (str);
	free(str);
	return (NULL);
}
