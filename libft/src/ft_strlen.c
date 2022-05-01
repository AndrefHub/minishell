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

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}

size_t	ft_strclen(char const *s, char set)
{
	size_t	i;

	i = 0;
	while (s[i] != set && s[i])
		++i;
	return (i);
}
