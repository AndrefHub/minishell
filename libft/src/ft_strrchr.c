/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_atoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 14:50:12 by kdancy            #+#    #+#             */
/*   Updated: 2021/11/08 15:41:11 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	strlen;

	strlen = ft_strlen(s);
	if (c == 0)
		return ((char *)s + strlen);
	i = 0;
	while (i < strlen)
	{
		if (s[strlen - i - 1] == (char)c)
			return ((char *)s + (strlen - i - 1));
		++i;
	}
	return (NULL);
}
