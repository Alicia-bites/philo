/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_does.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:49:43 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/06 11:21:10 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	ft_print(t_philo *philo, char *whattodo)
{
	int	err;
	
	err = 0;
	// err = pthread_mutex_lock(&philo->printf_mutex);
	printf("%lu %d %s\n", philo->timestamp, philo->id, whattodo);
	// err = pthread_mutex_unlock(&philo->printf_mutex);
	return (err);
}

int ft_do(t_philo *philo, unsigned long time_to, char *whattodo)
{
	int err;

	// printf("time_to = %lu | timestamp = %lu\n", time_to, philo->timestamp);
	err = 0;
	err = philo_starved(philo);
	err = pthread_mutex_lock(&philo->state->game_over_lock);
	if (!philo->state->game_over)
		ft_print(philo, whattodo);
	err = pthread_mutex_unlock(&philo->state->game_over_lock);
	philo->timestamp += time_to;
	wait_until(philo->timestamp, 0);
	// puts("hey");
	// printf(" philo ID : %d | timestamp %ld\n", philo->id, philo->timestamp);
	return (err);
}

int	philo_eats(t_philo *philo)
{
	int	err;

	err = grab_forks(philo);
	philo->last_eat = philo->timestamp;
	// printf("philo ID : %d | last_eat = %ld\n", philo->id, philo->last_eat);
	// printf("philo ID : %d | philo->timestamp = %ld\n", philo->id, philo->timestamp);
	err = ft_do(philo, philo->state->set.time_to_eat, EAT);
	err = drop_forks(philo);
	philo->n_meals++;
	// printf("n_meals for %d = %d\n", philo->id, philo->n_meals++);
	return (err);
}

int	philo_sleeps(t_philo *philo)
{
	int	err;
	
	// printf("%d\n", philo->state->set.time_to_sleep);
	// printf("%lu\n", philo->timestamp);
	err = ft_do(philo, philo->state->set.time_to_sleep, SLEEP);
	return (err);
}

int	philo_thinks(t_philo *philo)
{
	int	err;
	
	err = ft_do(philo, 0, THINK);
	return (err);
}