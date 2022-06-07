/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:31:28 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/07 13:30:17 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//philos->n_meals -- actual number of meals eaten by the philo
//philos->state->set.n_meals -- number of meals set bu user.
int	game_is_over(t_philo *philos)
{
	int	game_over;

	if (philos->state->set.n_meals != -1 && philos->n_meals
		>= philos->state->set.n_meals)
		return (1);
	pthread_mutex_lock(&philos->state->game_over_lock);
	game_over = philos->state->game_over;
	pthread_mutex_unlock(&philos->state->game_over_lock);
	return (game_over);
}

//if last time philo has eaten + time_to_die is superior to philos->timestamp, 
//--> kill philo
int	philo_starved(t_philo *philos)
{
	int	err;

	err = 0;
	if ((philos->last_eat + philos->state->set.time_to_die) < philos->timestamp)
	{
		err = pthread_mutex_lock(&philos->state->game_over_lock);
		if (!philos->state->game_over)
			ft_print(philos, DIE);
		philos->state->game_over = 1;
		err = pthread_mutex_unlock(&philos->state->game_over_lock);
		return (err);
	}
	return (1);
}

// Init mutex that locks state->game_over variable. This way, only one thread 
// can change this value -- only one philo can die at a time.
int	init_end_game(t_game *state)
{
	int	err;

	state->game_over = 0;
	err = pthread_mutex_init(&state->game_over_lock, 0);
	return (err);
}
