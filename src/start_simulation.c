/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:37:07 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/31 17:47:53 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	sim_is_over(t_philo *philos)
{
	// printf("n meals %d\n", philos->n_meals);
	// printf("n meals %d\n", philos->state->set->n_meals);
	if (philos->n_meals != -1 && philos->n_meals == philos->state.set.n_meals)
		return (1);
	return (0);
}

unsigned long	get_time(t_philo *philos)
{
	struct timeval	start;
	
	gettimeofday(&start, 0);
	return (philos->starting_time = (start.tv_sec * 1000)
		+ (start.tv_usec / 1000));
}

void	*sim(void *param)
{
	t_philo *philo;
	philo = (t_philo *)param;
	while (!sim_is_over(philo))
	{
		philo_eats(philo);
		philo_sleeps(philo);
		philo_thinks(philo);
	}
	return (0);
}

int	start_simulation(t_philo *philos, t_game state)
{
	int	i;
	int err;

	i = 0;
	philos->starting_time = get_time(philos);
	// printf("%lu\n", philos->starting_time);
	while (i < state.set.n_philos)
	{
		err = pthread_create(&philos[i].thread, 0, &sim, &philos[i]);
		// printf("err = %d\n", err);
		if (err != 0)
			return (ft_panic(THREAD_ERROR));
		i++;
	}

	i = 0;
	while (i < state.set.n_philos)
	{
		pthread_join(philos[i].thread, 0);
		i++;
	}
	return (0);
}