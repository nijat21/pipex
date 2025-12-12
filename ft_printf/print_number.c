/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nismayil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:24:48 by nismayil          #+#    #+#             */
/*   Updated: 2024/12/02 14:24:50 by nismayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr_fd_copy(int n, int *count, int fd)
{
	long	num;
	char	temp;

	num = n;
	if (fd < 0)
		return ;
	if (num < 0)
	{
		write(fd, "-", 1);
		num *= -1;
		(*count)++;
	}
	if (num >= 10)
		ft_putnbr_fd_copy(num / 10, count, fd);
	temp = num % 10 + '0';
	write(fd, &temp, 1);
	(*count)++;
}

int	print_number(int num)
{
	int	count;

	count = 0;
	ft_putnbr_fd_copy(num, &count, 1);
	return (count);
}
