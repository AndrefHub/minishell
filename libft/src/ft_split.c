/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:31:01 by kdancy            #+#    #+#             */
/*   Updated: 2021/11/08 15:41:11 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft.h"

static size_t	words_count(char const *s, char c)
{
	size_t	words_count;
	size_t	word_len;

	words_count = 0;
	word_len = 0;
	while (*s != '\0')
	{
		if (word_len == 0 && *s != c && *s != '\0')
		{
			words_count++;
			word_len = 1;
		}
		else if (word_len == 1 && *s == c)
			word_len = 0;
		s++;
	}
	return (words_count);
}

static char	*ft_strcdup(const char *s, char c)
{
	size_t	i;
	char	*dup;

	i = -1;
	dup = (char *)malloc(sizeof(char) * (ft_strclen(s, c) + 1));
	while (s[++i] != c && s[i])
		dup[i] = s[i];
	dup[i] = '\0';
	return (dup);
}

void	*ft_freesplit(char **words)
{
	size_t	i;

	i = -1;
	while (words[++i])
		free(words[i]);
	free(words);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	size_t	i;

	i = 0;
	if (s)
		words = malloc(sizeof(char *) * (words_count(s, c) + 1));
	if (!s || !words)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			s++;
		if (*s != c && *s)
		{
			words[i] = ft_strcdup(s, c);
			if (!(words[i++]))
				return (ft_freesplit(words));
			s += ft_strclen(s, c);
		}
	}
	words[i] = NULL;
	return (words);
}
