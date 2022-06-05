/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:37:07 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/05 19:00:55 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	*game(void *param)
{
	t_philo *philo;
	philo = (t_philo *)param;
	wait_if_even_nb_of_philo(philo);
	while (!game_is_over(philo))
	{
		organize_queue_to_eat(philo);
		philo_eats(philo);
		philo_sleeps(philo);
		philo_thinks(philo);
	}
	return (0);
}

int	start_simulation(t_philo *philos_list, t_game *state)
{
	int	i;
	int err;

	i = 0;
	// printf("%lu\n", philos->starting_time);
	// printf("n philo = %d\n", state->set.n_philos);
	get_starting_time(philos_list);
	while (i < state->set.n_philos)
	{
		err = pthread_create(&philos_list[i].thread, 0, &game, &philos_list[i]);
		// printf("err = %d\n", err);
		if (err != 0)
			return (ft_panic(THREAD_ERROR));
		i++;
	}
	i = 0;
	while (i < state->set.n_philos)
	{
		pthread_join(philos_list[i].thread, 0);
		i++;
	}
	return (0);
}