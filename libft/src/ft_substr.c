/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strpart1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 14:49:55 by kdancy            #+#    #+#             */
/*   Updated: 2021/11/08 15:41:11 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft.h"

char	*ft_substr(char const *s, size_t start, size_t len)
{
	char	*substr;
	size_t	size;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	size = ft_strlen(s) - start;
	if (size > len)
		size = len;
	substr = (char *)malloc(size + 1);
	if (substr)
	{
		i = 0;
		while (i < size)
		{
			substr[i] = s[i + start];
			++i;
		}
		substr[i] = '\0';
	}
	return (substr);
}
