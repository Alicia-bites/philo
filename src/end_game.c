/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:31:28 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/05 14:10:29 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"


//philos->n_meals -- actual number of meals eaten by the philo
//philos->state->set.n_meals -- number of meals set bu user.
int	game_is_over(t_philo *philos)
{
	int	game_over;

	// printf("philos->n_meals = %d | philos->state->set.n_meals = %d\n",
	// 	 philos->n_meals, philos->state->set.n_meals);
	if (philos->state->set.n_meals != -1 && philos->n_meals >= philos->state->set.n_meals)
	{
		// printf("REACHED N MEALS\n");
		return (1);		
	}
	pthread_mutex_lock(&philos->state->game_over_lock);
	// printf("philos->state->game_over : %d\n", philos->state->game_over);
	game_over = philos->state->game_over;
	pthread_mutex_unlock(&philos->state->game_over_lock);
	return (game_over);
}

//if last time philo has eaten + time_to_die is superior to philos->timestamp, 
//--> kill philo
int philo_starved(t_philo *philos)
{
	int err;

	err = 0;
	// printf("hellooo\n");
	// printf("last_eat : %lu\n", philos->last_eat);
	// printf("philos->timestamp : %lu\n", philos->timestamp);
	// printf("last eat : %lu\n", philos->last_eat);
	// printf("%d\n", (philos->last_eat + philos->state->set.time_to_die) < philos->timestamp);
	if ((philos->last_eat + philos->state->set.time_to_die) < philos->timestamp)
	{
		// printf("last_eat : %lu\n", philos->last_eat);
		// printf("philos->timestamp : %lu\n", philos->timestamp);
		err = pthread_mutex_lock(&philos->state->game_over_lock);
		// printf("game_over = %d\n", philos->state->game_over);
		if (!philos->state->game_over)
			printf("%lu %d %s\n", philos->timestamp, philos->id, DIE);
		philos->state->game_over = 1;
		err = pthread_mutex_unlock(&philos->state->game_over_lock);
		// printf("err = %d\n", err);
		return (err);
	}
	return (1);
}

int	init_end_game(t_game *state)
{
	int	err;

	state->game_over = 0;
	err = pthread_mutex_init(&state->game_over_lock, 0);
	return (err);
}