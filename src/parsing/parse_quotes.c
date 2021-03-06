/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:36:28 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/10 18:14:51 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

#define SINGLEQ '\''
#define DOUBLEQ '\"'

char	*get_quote(char **input)
{
	size_t	q;
	char	to_find;
	char	*remainder;

	to_find = SINGLEQ;
	q = ft_strchr_num(*input, SINGLEQ);
	if (q > ft_strchr_num(*input, DOUBLEQ))
	{
		q = ft_strchr_num(*input, DOUBLEQ);
		to_find = '\"';
	}
	if (q == 0)
		q = ft_strchr_num(*input + 1, to_find) + 1 + 1;
	if (q > ft_strlen(*input))
		q = ft_strlen(*input);
	remainder = ft_strndup(*input, q);
	*input += q;
	return (remainder);
}

t_list	*parse_quotes(char *input)
{
	t_list	*quotes;
	t_list	*next;
	char	*tmp;

	quotes = NULL;
	tmp = input;
	while (ft_strlen(tmp))
		ft_lstadd_back(&quotes, ft_lstnew(get_quote(&tmp)));
	ft_lstadd_back(&quotes, NULL);
	next = quotes;
	return (next);
}
