/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:02:43 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/02 12:48:37 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

unsigned long	when_is_next_meal(t_philo *philos)
{
	unsigned long next_meal;
	
	if (philos->state.set.n_philos % 2 != 1)
	{
		if (philos->last_eat == (unsigned long) - 1)
			philos->last_eat = 0;
		return (0);
	}
	else if (philos->last_eat == (unsigned long) - 1)
	{
		if (philos->id == philos->state.set.n_philos)
			return (next_meal = 0);
		else if (philos->id % 2 == 0)
			return (next_meal = philos->state.set.time_to_eat);
		else
			return (next_meal = philos->state.set.time_to_eat * 2);
	}
	else
		return (next_meal = philos->last_eat + (3 * philos->state.set.time_to_eat));		
	return (0);
}

void	wait_to_eat(t_philo *philos)
{
	unsigned long	next_meal;
	
	next_meal = when_is_next_meal(philos);
	printf("philo ID %d | next_meal is in : %ld ms\n", philos->id, next_meal);
	ft_wait_until(next_meal, 0);
	philos->timestamp = next_meal;
}

void	wait_if_even_nb_of_philo(t_philo *philos)
{
	if (!(philos->id % 2))
	{
		philos->timestamp += philos->state.set.time_to_eat / 2;
		ft_wait_until(philos->timestamp, 0);
	}
}