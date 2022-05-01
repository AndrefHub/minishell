/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:09:51 by kdancy            #+#    #+#             */
/*   Updated: 2021/11/08 15:41:11 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft.h"

static void	ft_putnbr_base(int number, char *base, int fd)
{
	int		base_size;

	base_size = 10;
	if (base_size > 1)
	{
		if (number == -2147483648)
		{
			ft_putnbr_base(number / base_size, base, fd);
			write(fd, "8", 1);
		}
		else if (number < 0)
		{
			write(fd, "-", 1);
			ft_putnbr_base(-number, base, fd);
		}
		else
		{
			if (number > base_size - 1)
				ft_putnbr_base(number / base_size, base, fd);
			write(fd, (base + (number % base_size)), 1);
		}
	}
}

void	ft_putnbr_fd(int nbr, int fd)
{
	ft_putnbr_base(nbr, "0123456789", fd);
}
