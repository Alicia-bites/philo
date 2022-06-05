/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:02:43 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/05 19:27:49 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	organize_queue_to_eat(t_philo *philo)
{
	unsigned long next_meal;
	
	// wait_if_even_nb_of_philo(philo);
	// next_meal = 0;
	if (philo->state->set.n_philos % 2 != 1)
	{
		if (philo->last_eat == -1UL)
			philo->last_eat = 0;
		return ;
	}
	if (philo->last_eat == -1UL)
	{
		if (philo->id == philo->state->set.n_philos)
			next_meal = 0;
		else if (philo->id % 2 == 0)
			next_meal = philo->state->set.time_to_eat;
		else
			next_meal = philo->state->set.time_to_eat * 2;
	}
	else
		next_meal = philo->last_eat + 3 * philo->state->set.time_to_eat;
	// printf("next_meal is in : %lu\n", next_meal);
	wait_until(next_meal, 0);
	philo->timestamp = next_meal;
}

//wait half the time set to eat by user before starting if even n_philo
void	wait_if_even_nb_of_philo(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		philo->timestamp += philo->state->set.time_to_eat;
		wait_until(philo->timestamp, 0);
	}
}

void	wait_and_add_waited_time(t_philo *philo, unsigned long *time_waited)
{
	unsigned long	new_try;

	new_try = philo->timestamp + 0.2;
	// printf("%lu\n", new_try);
	wait_until(new_try, 0);
	*time_waited += 0.2;
	// printf("time waited = %lu\n", *time_waited);
	if (*time_waited > 1)
	{
		// *time_waited = 0;
		philo->timestamp++;
	}
}