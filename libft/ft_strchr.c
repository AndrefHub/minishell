/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 00:00:21 by lsherry           #+#    #+#             */
/*   Updated: 2021/10/13 00:00:25 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *s, int c)
{
	if (c == 0)
		return ((char *)s + ft_strlen(s));
	while (*s != (char)c && *s)
		s++;
	if (*s == (char)c)
		return (s);
	return (NULL);
}
