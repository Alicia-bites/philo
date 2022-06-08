/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:31:28 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/08 11:45:16 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//philo->n_meals -- actual number of meals eaten by the philo
//philo->diner->set.n_meals -- number of meals set bu user.
int	game_is_over(t_philo *philo)
{
	int	game_over;

	if (philo->diner->set.n_meals != -1 && philo->n_meals
		>= philo->diner->set.n_meals)
		return (1);
	pthread_mutex_lock(&philo->diner->game_over_lock);
	game_over = philo->diner->game_over;
	pthread_mutex_unlock(&philo->diner->game_over_lock);
	return (game_over);
}

//if last time philo has eaten + time_to_die is superior to philo->timestamp, 
//--> kill philo
int	philo_starved(t_philo *philo)
{
	int	err;

	err = 0;
	if ((philo->last_eat + philo->diner->set.time_to_die) < philo->timestamp)
	{
		err = pthread_mutex_lock(&philo->diner->game_over_lock);
		if (!philo->diner->game_over)
			color_print(philo, DIE);
		philo->diner->game_over = 1;
		err = pthread_mutex_unlock(&philo->diner->game_over_lock);
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
