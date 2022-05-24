/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 12:05:13 by amarchan          #+#    #+#             */
/*   Updated: 2021/12/13 12:31:20 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_u(unsigned int nb)
{
	int	len;

	len = 0;
	if (nb > 9)
	{
		len += ft_print_u(nb / 10);
		len += ft_print_u(nb % 10);
	}
	else
	{
		ft_putchar(nb + '0');
		len++;
	}
	return (len);
}
