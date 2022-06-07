/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:37:07 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/07 13:47:48 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

//start game simulation. 
void	*game(void *param)
{
	t_philo	*philo;

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

//1.create one thread per philo, passing in second argument the function that
//	will define what the thread/philo will be doing.
//2.make the program wait until each thread/philo is finished doing what it has
//	to do and once they are all back continue and end the program.
int	start_simulation(t_philo *philos_list, t_game *state)
{
	int	i;
	int	err;

	i = 0;
	get_starting_time();
	while (i < state->set.n_philos)
	{
		err = pthread_create(&philos_list[i].thread, 0, &game, &philos_list[i]);
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
