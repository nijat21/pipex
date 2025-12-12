/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nismayil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:25:37 by nismayil          #+#    #+#             */
/*   Updated: 2024/12/02 14:25:39 by nismayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_string(char *str)
{
	if (!str)
		str = "(null)";
	if (*str == '\0')
		return (0);
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}
