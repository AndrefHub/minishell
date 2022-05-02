/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 00:00:27 by lsherry           #+#    #+#             */
/*   Updated: 2021/10/13 00:00:28 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	unsigned int	len;
	char			*dup;
	unsigned int	i;

	i = 0;
	len = ft_strlen(s);
	dup = (char *) malloc(len + 1 * sizeof(char));
	if (dup == NULL)
		return (NULL);
	while (i < len && s[i] != '\0')
	{
		dup[i] = *(char *)(s + i);
		i++;
	}
	if (i >= 0)
		dup[i] = '\0';
	return (dup);
}
