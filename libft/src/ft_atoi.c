/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_atoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 14:50:12 by kdancy            #+#    #+#             */
/*   Updated: 2021/11/08 15:41:11 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft.h"

int	ft_atoi(const char *str)
{
	int	number;
	int	counter;
	int	sign;

	number = 0;
	counter = 0;
	sign = -1;
	while (*str == '\t' || *str == '\n' || *str == '\r' || *str == '\v'
		|| *str == '\f' || *str == ' ')
		++str;
	if (*str == '-' || *str == '+')
	{
		sign += 2 * (*str == '-');
		++str;
	}
	while (*str == '0')
		++str;
	while (ft_isdigit(str[counter]) && counter < 10)
	{
		number = (10 * number) - (str[counter] - '0');
		++counter;
	}
	return (number * sign);
}
