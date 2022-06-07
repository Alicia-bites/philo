/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:31:28 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/07 14:43:44 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//philos->n_meals -- actual number of meals eaten by the philo
//philos->diner->set.n_meals -- number of meals set bu user.
int	game_is_over(t_philo *philos)
{
	int	game_over;

	if (philos->diner->set.n_meals != -1 && philos->n_meals
		>= philos->diner->set.n_meals)
		return (1);
	pthread_mutex_lock(&philos->diner->game_over_lock);
	game_over = philos->diner->game_over;
	pthread_mutex_unlock(&philos->diner->game_over_lock);
	return (game_over);
}

//if last time philo has eaten + time_to_die is superior to philos->timestamp, 
//--> kill philo
int	philo_starved(t_philo *philos)
{
	int	err;

	err = 0;
	if ((philos->last_eat + philos->diner->set.time_to_die) < philos->timestamp)
	{
		err = pthread_mutex_lock(&philos->diner->game_over_lock);
		if (!philos->diner->game_over)
			ft_print(philos, DIE);
		philos->diner->game_over = 1;
		err = pthread_mutex_unlock(&philos->diner->game_over_lock);
		return (err);
	}
	return (1);
}

// Init mutex that locks diner->game_over variable. This way, only one thread 
// can change this value -- only one philo can die at a time.
int	init_end_game(t_game *diner)
{
	int	err;

	diner->game_over = 0;
	err = pthread_mutex_init(&diner->game_over_lock, 0);
	return (err);
}
