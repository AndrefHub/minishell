/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funny_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:12:17 by andref            #+#    #+#             */
/*   Updated: 2022/05/01 12:18:53 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strcat_delim(char *first, char delim, char *second)
{
	char	*dup;
	size_t	flen;
	size_t	slen;
	int		fcounter;
	int		scounter;

	fcounter = -1;
	scounter = -1;
	flen = ft_strlen(first);
	slen = ft_strlen(second);
	dup = (char *)malloc(sizeof(char) * (flen + 1 + slen + 1));
	if (!dup)
		return (NULL);
	while (first[++fcounter])
		dup[fcounter] = first[fcounter];
	dup[fcounter++] = delim;
	while (second[++scounter])
		dup[fcounter + scounter] = second[scounter];
	dup[fcounter + scounter] = '\0';
	return (dup);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && (s1[i] == s2[i]))
		++i;
	return (s1[i] - s2[i]);
}
