/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:31:01 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/01 14:57:24 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft.h"

#define FT_SPACE "\t "
#define FT_DELIM |&<>

static int	is_in(char c, char *set)
{
	int counter;

	counter = -1;
	while (set[++counter])
	{
		if (c == set[counter])
			return (counter);
		++set;
	}
	return (-1);
}

static size_t	words_count(char const *s)
{
	size_t	words_count;
	size_t	word_len;

	words_count = 0;
	word_len = 0;
	while (*s != '\0')
	{
		if (word_len == 0 && is_in(s, FT_SPACE) == -1 && *s != '\0')
		{
			words_count++;
			word_len = 1;
		}
		else if (word_len == 1 && is_in(s, FT_SPACE))
			word_len = 0;
		s++;
	}
	return (words_count);
}

static char	*ft_strcdup(const char *s, char *set)
{
	size_t	i;
	int		len;
	char	*dup;

	i = -1;
	len = 727272727;
	while (set[++i])
		if (ft_strclen(s, set[i]) < len)
			len = ft_strclen(s, set[i]);
	dup = (char *)malloc(sizeof(char) * (len + 1));
	i = -1;
	while (!is_in(s[++i], set) && s[i])
		dup[i] = s[i];
	dup[i] = '\0';
	return (dup);
}

char	**ft_split(char const *s)
{
	char	**words;
	size_t	i;

	i = 0;
	if (s)
		words = malloc(sizeof(char *) * (words_count(s) + 1));
	if (!s || !words)
		return (NULL);
	while (*s)
	{
		if (is_in(*s, FT_SPACE))
			s++;
		if (!is_in(*s, FT_SPACE) && *s)
		{
			words[i] = ft_strcdup(s, FT_SPACE);
			if (!(words[i++]))
				return (ft_freesplit(words));
			s += ft_strclen(s, words[i - 1]);
		}
	}
	words[i] = NULL;
	return (words);
}
