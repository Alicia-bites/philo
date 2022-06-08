/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_diner.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:37:07 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/07 14:43:44 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

// Start game.
void	*game(void *param)
{
	t_philo	*philo;
	int		err;

	err = 0;
	philo = (t_philo *)param;
	hold_philo_if_even_ID(philo);
	while (!game_is_over(philo))
	{
		organize_queue_to_eat(philo);
		err = philo_eats(philo);
		err = philo_sleeps(philo);
		err = philo_thinks(philo);
	}
	if (err)
	{
		printf("%d\n", err);
		return (0);
	}
	return (0);
}

//1. Create one thread per philo, passing in second argument the function that
//	will define what the thread/philo will be doing.
//2. Make the program wait until each thread/philo is finished doing what it 
// has to do and once they are all back continue and end the program.
int	start_diner(t_philo *philos_list, t_game *diner)
{
	int	i;
	int	err;

	i = 0;
	get_starting_time(philos_list);
	while (i < diner->set.n_philos)
	{
		err = pthread_create(&philos_list[i].thread, 0, &game, &philos_list[i]);
		if (err != 0)
			return (ft_panic(THREAD_ERROR));
		i++;
	}
	i = 0;
	while (i < diner->set.n_philos)
	{
		pthread_join(philos_list[i].thread, 0);
		i++;
	}
	return (0);
}
