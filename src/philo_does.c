/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_does.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:49:43 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/02 17:47:07 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"



int ft_do(t_philo *philos, unsigned long time_to, char *whattodo)
{
	int err;

	err = 0;
	// err = kill_philo_if_he_starved(philos);
	err = pthread_mutex_lock(&philos->state.game_over_lock);
	if (!philos->state.game_over)
		printf("%lu %d %s\n", philos->timestamp, philos->id, whattodo);
	err = pthread_mutex_unlock(&philos->state.game_over_lock);
	philos->timestamp += time_to;
	ft_wait_until(philos->timestamp, 0);
	// printf(" philo ID : %d | timestamp %ld\n", philos->id, philos->timestamp);
	return (0);
}

int	philo_eats(t_philo *philos)
{
	int	err;

	err = grab_forks(philos);
	
	philos->last_eat = philos->timestamp;
	// printf("philo ID : %d | last_eat = %ld\n", philos->id, philos->last_eat);
	// printf("philo ID : %d | philos->timestamp = %ld\n", philos->id, philos->timestamp);
	philos->timestamp += philos->state.set.time_to_eat;
	err = ft_do(philos, philos->state.set.time_to_eat, EAT);
	err = drop_forks(philos);
	philos->n_meals++;
	// printf("n_meals for %d = %d\n", philos->id, philos->n_meals++);
	return (err);
}

int	philo_sleeps(t_philo *philos)
{
	int	err;
	
	// printf("%d\n", philos->state.set.time_to_sleep);
	// printf("%lu\n", philos->timestamp);
	err = ft_do(philos, philos->state.set.time_to_sleep, SLEEP);
	return (err);
}

int	philo_thinks(t_philo *philos)
{
	int	err;
	
	err = ft_do(philos, 0, THINK);
	return (err);
}