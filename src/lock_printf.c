/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:54:31 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/07 13:32:15 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_printf_lock(t_philo *philos)
{
	int	err;

	err = pthread_mutex_init(&philos->printf_mutex, 0);
	return (err);
}
