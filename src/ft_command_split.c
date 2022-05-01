#include "../minishell.h"

int	is_in(char c, char *set)
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

size_t	command_words_count(char **args)
{
	size_t	counter;
	size_t	words_count;
	size_t	word_len;

	words_count = 0;
	word_len = 0;
	while (*args)
	{
		counter = 0;
		while ((*args)[counter])
		{
			if (is_in((*args)[counter], FT_DELIM) >= 0 && is_in((*args)[counter], FT_DELIM) == is_in((*args)[counter + 1], FT_DELIM))
			{
				if (counter > 0 || counter < ft_strlen(*args))
					++words_count;
				++words_count;
				++counter;
			}
			else if (is_in((*args)[counter], FT_DELIM) >= 0)
			{
				if (counter > 0 || counter < ft_strlen(*args))
					++words_count;
				++words_count;
			}
			++counter;
		}
		++args;
	}
	return (words_count);
}

// char	**ft_command_split(char **args)
// {
// 	char	**words;
// 	int		i;
// 	int		c;
// 	char	*word;

// 	i = 0;
// 	if (args)
// 		words = malloc(sizeof(char *) * (words_count(args) + 1));
// 	if (!args || !words)
// 		return (NULL);
// 	while (*args)
// 	{
// 		word = *args;
// 		c = 0;
// 		while (*word)
// 		{
// 			if (is_in(word[c], FT_DELIM) >= 0 && is_in(word[c], FT_DELIM) == is_in(word[c + 1], FT_DELIM))
// 			{
// 				if (c > 0 || c < ft_strlen(word))
// 					;
// 				++words_count;
// 				++c;
// 			}
// 			else if (is_in((*args)[c], FT_DELIM) >= 0)
// 			{
// 				if (i > 0 || i < ft_strlen(*args))
// 					++words_count;
// 				++words_count;
// 			}
// 			++c;
// 		}
// 		++args;
// 	}
// 	words[i] = NULL;
// 	return (words);
// }
