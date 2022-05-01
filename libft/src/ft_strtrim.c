/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:22:59 by kdancy            #+#    #+#             */
/*   Updated: 2021/11/08 15:41:11 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft.h"

static int	ft_is_in_set(char symbol, char const *set)
{
	while (*set)
	{
		if (symbol == *set)
			return (1);
		++set;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	begin;
	size_t	end;
	size_t	counter;
	size_t	to_alloc;
	char	*trimmed;

	if (!s1 || !set)
		return (NULL);
	begin = 0;
	end = ft_strlen(s1);
	while (begin < end && ft_is_in_set(s1[begin], set))
		++begin;
	while (begin < end && ft_is_in_set(s1[end - 1], set))
		--end;
	to_alloc = end - begin + 1;
	trimmed = (char *)malloc(sizeof(char) * (to_alloc));
	if (!trimmed)
		return (NULL);
	counter = -1;
	while (begin + ++counter < end)
		trimmed[counter] = s1[begin + counter];
	trimmed[counter] = '\0';
	return (trimmed);
}
