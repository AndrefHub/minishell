/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 21:59:01 by lsherry           #+#    #+#             */
/*   Updated: 2022/05/01 17:26:14 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_isin(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	i_word(char *str, char *charset)
{
	int	i;

	i = 0;
	while (*str)
	{
		while (*str && ft_isin(*str, charset))
			str++;
		if (*str && !ft_isin(*str, charset))
		{
			i++;
			while (*str && !ft_isin(*str, charset))
				str++;
		}
	}
	return (i);
}

char	*crt_word(char *str, char *charset)
{
	char	*word;
	int		i;

	i = 0;
	while (str[i] && !ft_isin(str[i], charset))
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] && !ft_isin(str[i], charset))
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split_space(char *str, char *charset)
{
	char	**arr;
	int		i;

	i = 0;
	if (str && charset)
		arr = (char **)malloc(sizeof(char *) * (i_word(str, charset) + 1));
	else
		return (NULL);
	while (*str)
	{
		while (*str && ft_isin(*str, charset))
			str++;
		if (*str && !ft_isin(*str, charset))
		{
			arr[i] = crt_word(str, charset);
			i++;
			while (*str && !ft_isin(*str, charset))
				str++;
		}
	}
	arr[i] = NULL;
	return (arr);
}

