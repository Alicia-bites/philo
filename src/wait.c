/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:02:43 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/05 14:58:01 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	organize_queue_to_eat(t_philo *philos)
{
	unsigned long next_meal;
	
	wait_if_even_nb_of_philo(philos);
	next_meal = 0;
	if (philos->state->set.n_philos % 2 != 1)
	{
		if (philos->last_eat == -1UL)
			philos->last_eat = 0;
		return ;
	}
	if (philos->last_eat == -1UL)
	{
		if (philos->id == philos->state->set.n_philos)
			next_meal = 0;
		else if (philos->id % 2 == 0)
			next_meal = philos->state->set.time_to_eat;
		else
			next_meal = philos->state->set.time_to_eat * 2;
	}
	else
		next_meal = philos->last_eat + (3 * philos->state->set.time_to_eat);
	// printf("next_meal is in : %lu\n", next_meal);
	wait_until(next_meal, 0);
	philos->timestamp = next_meal;
}

//wait half the time set to eat by user before starting if even n_philos
void	wait_if_even_nb_of_philo(t_philo *philos)
{
	if (!(philos->id % 2))
	{
		philos->timestamp += philos->state->set.time_to_eat;
		wait_until(philos->timestamp, 0);
	}
}

void	wait_and_add_waited_time(t_philo *philos, unsigned long *time_waited)
{
	unsigned long	new_try;

	new_try = philos->timestamp + 0.2;
	wait_until(new_try, 0);
	*time_waited += 0.2;
	if (*time_waited > 1000)
	{
		*time_waited = 0;
		philos->timestamp++;
	}
}