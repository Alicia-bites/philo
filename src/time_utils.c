/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:09:08 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/09 10:39:21 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

struct timeval	ft_convert(unsigned long moment_ms)
{
	struct timeval	moment_converted;

	moment_converted.tv_sec = moment_ms / 1000;
	moment_converted.tv_usec = moment_ms % 1000 * 1000;
	return (moment_converted);
}

int	greater_than(unsigned long a, unsigned long b)
{
	if (a > b)
		return (1);
	return (0);
}

unsigned long	time_sub(struct timeval a, struct timeval b)
{
	unsigned long	a_long;
	unsigned long	b_long;

	a_long = a.tv_sec * 1000 + a.tv_usec / 1000;
	b_long = b.tv_sec * 1000 + b.tv_usec / 1000;
	return (a_long - b_long);
}
