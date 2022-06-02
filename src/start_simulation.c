/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:37:07 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/02 12:36:56 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	game_is_over(t_philo *philos)
{
	// printf("n meals %d\n", philos->n_meals);
	// printf("n meals %d\n", philos->state.set->n_meals);
	if (philos->n_meals != -1 && philos->n_meals == philos->state.set.n_meals)
		return (1);
	return (0);
}

void	*sim(void *param)
{
	t_philo *philo;
	philo = (t_philo *)param;
	wait_if_even_nb_of_philo(philo);
	// printf("is game over? %d\n", game_is_over(philo));
	// printf("starting time baby : %lu\n", philo->starting_time);
	while (!game_is_over(philo))
	{
		wait_to_eat(philo);
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
	// printf("%lu\n", philos->starting_time);
	// printf("n philo = %d\n", state.set.n_philos);
	get_starting_time(philos);
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