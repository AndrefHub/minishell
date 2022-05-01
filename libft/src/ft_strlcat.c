/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mempart2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 14:49:40 by kdancy            #+#    #+#             */
/*   Updated: 2021/11/08 15:41:11 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	dstfill;
	size_t	srclen;
	size_t	srcfill;

	dstlen = 0;
	srclen = 0;
	while (dstlen < dstsize && dst[dstlen])
		++dstlen;
	srcfill = dstsize - dstlen;
	dstfill = dstlen;
	if (srcfill-- == 0)
		return (dstlen + ft_strlen(src));
	while (src[srclen])
	{
		if (srcfill)
		{
			dst[dstfill++] = src[srclen];
			--srcfill;
		}
		++srclen;
	}
	dst[dstfill] = '\0';
	return (dstlen + srclen);
}
