/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:17:53 by kdancy            #+#    #+#             */
/*   Updated: 2021/11/08 15:41:11 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft.h"

char	*ft_strnstr(char *str, char *substr, size_t n)
{
	char	*strend;
	size_t	substr_len;

	strend = str + n;
	substr_len = ft_strlen(substr);
	if (!substr_len)
		return (str);
	strend -= substr_len - 1;
	while (str < strend)
	{
		if (!ft_strncmp(str, substr, substr_len))
			return (str);
		++str;
	}
	return (NULL);
}
