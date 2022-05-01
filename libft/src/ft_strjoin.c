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

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	l1;
	size_t	l2;
	size_t	i;
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	join = (char *)malloc(sizeof(char) * (l1 + l2 + 1));
	if (!join)
		return (NULL);
	i = -1;
	while (++i < l1)
		join[i] = s1[i];
	i = -1;
	while (++i < l2)
		join[l1 + i] = s2[i];
	join[l1 + l2] = '\0';
	return (join);
}
