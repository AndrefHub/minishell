/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:06:30 by kdancy            #+#    #+#             */
/*   Updated: 2021/11/08 15:41:11 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft.h"

static int	ft_number_size(int n, int sign)
{
	int	size;

	size = 0;
	if (sign > 0)
		++size;
	while (n != 0)
	{
		n /= 10;
		++size;
	}
	return (size + 1);
}

static void	ft_swap(char *lhs, char *rhs)
{
	char	buf;

	buf = *lhs;
	*lhs = *rhs;
	*rhs = buf;
}

static void	ft_reverse(char **num)
{
	size_t	index;

	index = -1;
	while (++index < ft_strlen(*num) / 2)
		ft_swap(*num + index, *num + ft_strlen(*num) - index - 1);
}

static void	zero(char **num)
{
	(*num) = malloc(2);
	(*num)[0] = '0';
	(*num)[1] = '\0';
}

char	*ft_itoa(int n)
{
	int		sign;
	size_t	index;
	char	*num;

	if (n == 0)
		zero(&num);
	if (n == 0)
		return (num);
	index = 0;
	sign = -1 + 2 * (n < 0);
	n *= sign;
	num = (char *)malloc(sizeof(char) * ft_number_size(n, sign));
	if (!num)
		return (NULL);
	while (n != 0)
	{
		num[index++] = '0' - n % 10;
		n /= 10;
	}
	if (sign > 0)
		num[index++] = '-';
	num[index] = '\0';
	ft_reverse(&num);
	return (num);
}
