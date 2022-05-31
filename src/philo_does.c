/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_does.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:49:43 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/31 17:48:33 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int kill_philo_if_he_starved(t_philo *philos)
{
	if (philos->last_eat + philos->state.set.time_to_die < philos->timestamp)
	{
		philos->timestamp = get_time - philos->starting_time;
		printf("%d\n %d\n died\n", philos->timestamp - philos->starting_time,
			philos->id);
	}
	return (0);
}
int	is_eating(t_philo *philos, int time_to)
{
	int err;

	err = kill_philo_if_he_starved(*philos);
	printf("%d %d is eating\n", philos->timestamp - philos->starting_time,
		philos->id);
	return (0);
}

int	philo_eats(t_philo *philos)
{
	int	err;

	grab_fork(philos, philos->right_fork);
	grab_fork(philos, philos->left_fork);
	philos->last_eat = philos->timestamp;
	err = is_eating(philos, philos->state.set.time_to_eat);
	printf("%ld %d is eating\n", philos->timestamp, philos->id);
	philos->timestamp += philos->state.set.time_to_eat;
	printf("n_meals for %d = %d\n", philos->id, philos->n_meals++);
	release_fork(philos->left_fork);
	release_fork(philos->right_fork);
	philos->n_meals++;
	return (err);
}

void	philo_sleeps(t_philo *philos)
{
	printf("%ld %d is sleeping\n", philos->timestamp, philos->id);
	// printf("before : %ld\n", philos->timestamp);
	philos->timestamp += philos->state.set.time_to_sleep;
	// printf("after : %ld\n", philos->timestamp);
}

void	philo_thinks(t_philo *philos)
{
	printf("%ld %d is thinking\n", philos->timestamp, philos->id);
}