/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_px.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:19:40 by amarchan          #+#    #+#             */
/*   Updated: 2021/12/13 12:49:50 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_nbrlen(long unsigned int nbr)
{
	int	i;

	i = 0;
	while (nbr > 0)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

static int	ft_check_base(char *base)
{
	int	i;
	int	z;

	i = 0;
	z = 0;
	if (base[0] == '\0' || base[1] == '\0')
		return (0);
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		if (base[i] < 32 || base[i] > 126)
			return (0);
		z = i + 1;
		while (base[z])
		{
			if (base[i] == base[z])
				return (0);
			z++;
		}
		i++;
	}
	return (1);
}

static int	ft_print(long unsigned int *nbr_final, long unsigned int nbr,
		int size_base, char *base)
{
	int	i;
	int	len;
	int	nbr_base;

	i = 0;
	len = 0;
	nbr_base = ft_nbrlen(nbr);
	while (nbr_base--)
	{
		while (nbr != 0)
		{
			nbr_final[i] = nbr % size_base;
			nbr = nbr / size_base;
			i++;
			len = i;
		}
		while (--i >= 0)
			ft_putchar(base[nbr_final[i]]);
	}
	return (len);
}

int	ft_px(long unsigned int nbr, char *base)
{
	int					size_base;
	long unsigned int	*nbr_final;
	int					len;
	int					nbr_size;

	size_base = 0;
	nbr_size = ft_nbrlen(nbr);
	if (nbr == 0)
		return (ft_putstr_n("0"));
	nbr_final = (long unsigned int *)malloc(sizeof(long unsigned int)
			* nbr_size);
	if (!nbr_final)
		return (0);
	if (ft_check_base(base))
		size_base = ft_strlen(base);
	len = ft_print(nbr_final, nbr, size_base, base);
	free(nbr_final);
	return (len);
}
