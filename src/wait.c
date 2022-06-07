/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:02:43 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/07 14:43:44 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

// Organize the order in each philosophers are going to eat. If uneven number
// of philo, always start with the highest ID, then the philosophers with an 
// even ID, then, the philosphers with an uneven ID.
// If even number of philosophers, just set the last_meal variable at 0.
void	organize_queue_to_eat(t_philo *philo)
{
	unsigned long	next_meal;

	next_meal = 0;
	if (philo->diner->set.n_philos % 2 != 1)
	{
		if (philo->last_eat == -1UL)
			philo->last_eat = 0;
		return ;
	}
	if (philo->last_eat == -1UL)
	{
		if (philo->id == philo->diner->set.n_philos)
			next_meal = 0;
		else if (philo->id % 2 == 0)
			next_meal = philo->diner->set.time_to_eat;
		else
			next_meal = philo->diner->set.time_to_eat * 2;
	}
	else
		next_meal = philo->last_eat + 3 * philo->diner->set.time_to_eat;
	wait_until(next_meal, 0);
	philo->timestamp = next_meal;
}

//wait half the time set to eat by user before starting if even n_philo
void	wait_if_even_nb_of_philo(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		philo->timestamp += philo->diner->set.time_to_eat / 2;
		wait_until(philo->timestamp, 0);
	}
}

//wait and update timestamp with waited time
void	wait_and_add_waited_time(t_philo *philo, double *time_waited)
{
	unsigned long	new_try;

	new_try = philo->timestamp + 0.2;
	wait_until(new_try, 0);
	*time_waited = *time_waited + 0.2;
	if (*time_waited > 1)
	{
		*time_waited = 0;
		philo->timestamp++;
	}
}
