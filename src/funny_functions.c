/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funny_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:12:17 by andref            #+#    #+#             */
/*   Updated: 2022/05/02 11:02:16 by kdancy           ###   ########.fr       */
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

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*dup;
	
	len = ft_strlen(s);
	if (len > n)
		len = n;
	dup = (char *) malloc(len + 1);
	if (dup == NULL)
		return NULL;
	dup[len] = '\0';
	return ((char *) ft_memcpy(dup, s, len));
}

int	ft_strchr_num(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		++i;
	if (c == s[i])
		return (i);
	return (i + 1);
}