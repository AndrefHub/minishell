/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lol.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 21:04:28 by kdancy            #+#    #+#             */
/*   Updated: 2022/05/15 21:04:46 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_lst_to_char(t_list *lst)
{
	char	*str;

	str = malloc(1);
	str[0] = '\0';
	while (lst)
	{
		str = ft_strjoin_gnl(str, (char *)lst->content);
		lst = lst->next;
	}
	return (str);
}
