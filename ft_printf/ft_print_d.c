/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 12:04:35 by amarchan          #+#    #+#             */
/*   Updated: 2021/12/13 12:37:56 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_int_min(int len)
{
	(void) len;
	write(1, "-2147483648", 11);
	return (11);
}

int	ft_print_d(int nb)
{
	int	len;

	len = 0;
	if (nb == -2147483648)
	{
		len = ft_int_min(len);
		return (11);
	}
	if (nb < 0)
	{
		ft_putchar('-');
		nb *= -1;
		len++;
	}
	if (nb > 9)
	{
		len += ft_print_d(nb / 10);
		len += ft_print_d(nb % 10);
	}
	else
	{
		ft_putchar(nb + '0');
		len++;
	}
	return (len);
}
