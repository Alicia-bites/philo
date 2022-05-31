/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_fork_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:26:40 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/31 17:21:41 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	wait(t_philo *philos)
{
	return (0);
}

int	try(t_philo *philos, t_fork fork)
{
	int	err;
	int	can_take_fork;

	can_take_fork = 0;
	pthread_mutex_lock(&fork.fork_is_taken);
	if (!fork.fork_id)
	{
		fork.fork_id = philos.id;
		can_take_fork = 1;
	}
	pthread_mutex_unlock(&fork.fork_id);
	err = 0;
	if (can_take_fork)
		return(1);
	if (err)
		return (-1);
	return (can_take_fork);
	
}

int	can_eat(t_philo *philos)
{
	int	can_eat;

	can_eat = try(philos, philos.right_fork);
	can_eat = try(philos, philos.left_fork);
	if (can_eat)
		return (1);
	else
		// wait(philos);
	return (0);
}