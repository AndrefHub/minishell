/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:55:54 by lsherry           #+#    #+#             */
/*   Updated: 2021/11/06 11:55:55 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	if (c == 0)
		return ((char *)s + i);
	while (*s != (char)c && *s)
		s++;
	if (*s == (char)c)
		return (s);
	return (NULL);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	len;
	size_t	i;
	char	*buf;
	char	*tmp;

	if (!s1 || !s2)
		return (NULL);
	tmp = s1;
	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	buf = (char *) malloc(len * sizeof(char) + 1);
	if (!buf)
		return (NULL);
	while (*s1 != '\0')
		buf[i++] = *s1++;
	while (*s2 != '\0')
		buf[i++] = *s2++;
	buf[i] = '\0';
	free(tmp);
	return (buf);
}

char	*ft_strdup(const char *s)
{
	unsigned int	len;
	char			*dup;
	unsigned int	i;

	i = 0;
	len = ft_strlen(s);
	dup = (char *) malloc(len + 1 * sizeof(char));
	if (!dup)
		return (NULL);
	while (i < len && s[i] != '\0')
	{
		dup[i] = *(char *)(s + i);
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
