/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_str_in_lst.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:37:30 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/10 17:37:31 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_split_tools(char *str, int i, char *pattern, t_list *elem)
{
	int	len;

	len = ft_find_substr(&str[i], pattern);
	if (len != -1)
	{
		if (len == 0)
			ft_lstadd_back(&elem, ft_lstnew(ft_strdup(pattern)));
		else
		{
			ft_lstadd_back(&elem, ft_lstnew(ft_strndup(&str[i], len)));
			ft_lstadd_back(&elem, ft_lstnew(ft_strdup(pattern)));
		}
		return (len + (int )ft_strlen(pattern));
	}
	else
	{
		ft_lstadd_back(&elem, ft_lstnew(ft_strdup(&str[i])));
		return (-1);
	}
}

static int	ft_is_true_pattern(char *str, int len, char *pattern, int mode)
{
	if (mode)
		return (!str || str[0] == '"' || str[0] == '\'' || str
			[ft_strlen(str)] == '"' || str[ft_strlen(str)] == '\'' || len == -1
			|| (len == 0 && ft_strlen(str) == ft_strlen(pattern)));
	else
		return (!str || str[0] == '\'' || str[ft_strlen(str)] == '\''
			|| len == -1 || (len == 0 && ft_strlen(str) == ft_strlen(pattern)));
}

void	ft_split_first_iter(int len, t_list *elem, char *pattern, char *str)
{
	if (len == 0)
		elem->content = ft_strdup(pattern);
	else
	{
		elem->content = ft_strndup(str, len);
		ft_lstadd_back(&elem, ft_lstnew(ft_strdup(pattern)));
	}
}

t_list	*ft_split_str_in_lst(char *pattern, t_list *elem, int mode)
{
	t_list	*next;
	int		len;
	int		i;
	char	*str;

	if (!elem)
		return (NULL);
	str = elem->content;
	len = ft_find_substr(str, pattern);
	if (ft_is_true_pattern(str, len, pattern, mode))
		return (elem);
	next = elem->next;
	elem->next = NULL;
	ft_split_first_iter(len, elem, pattern, str);
	i = len + (int) ft_strlen(pattern);
	while (str[i])
	{
		len = ft_split_tools(str, i, pattern, elem);
		i += len;
		if (!str[i] || len == -1)
			break ;
	}
	free(str);
	ft_lstlast(elem)->next = next;
	return (elem);
}
