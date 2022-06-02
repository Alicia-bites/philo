/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:31:28 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/02 19:09:56 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	game_is_over(t_philo *philos)
{
	int	game_over;
	
	if (philos->n_meals != -1 && philos->n_meals == philos->state.set.n_meals)
		return (1);
	pthread_mutex_lock(&philos->state.game_over_lock);
	game_over = philos->state.game_over;
	pthread_mutex_unlock(&philos->state.game_over_lock);
	return (game_over);
}

int kill_philo_if_he_starved(t_philo *philos)
{
	int err;

	err = 0;
	// printf("hellooo\n");
	// printf("timestamp : %lu\n", philos->timestamp);
	// printf("last_eat : %d\n", (int)philos->last_eat);
	printf("%d\n", (philos->last_eat + philos->state.set.time_to_die) > philos->timestamp);
	if ((philos->last_eat + philos->state.set.time_to_die) > philos->timestamp)
	{
		err = pthread_mutex_lock(&philos->state.game_over_lock);
		if (!philos->state.game_over)
			ft_do(philos, philos->timestamp, DIE);
		philos->state.game_over = 1;
		err = pthread_mutex_unlock(&philos->state.game_over_lock);
	}
	return (err);
}

int	init_end_game(t_game state)
{
	int	err;

	state.game_over = 0;
	err = pthread_mutex_init(&state.game_over_lock, 0);
	return (err);
}