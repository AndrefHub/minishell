/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:37:41 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/15 12:22:30 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_in(char c, const char *set)
{
	int	counter;

	counter = -1;
	while (set[++counter])
	{
		if (c == set[counter])
			return (1);
	}
	return (0);
}

void	split_by_pattern(t_list **lst, char *pattern, int mode)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		ft_split_str_in_lst(pattern, tmp, mode);
		tmp = tmp->next;
	}
}
