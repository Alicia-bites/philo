/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_does.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:49:43 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/08 13:52:04 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

// Print what philosophers are doing at philo->timestamp with colors.
void	color_print(t_philo *philo, int whattodo)
{
	if (whattodo == EAT)
		printf("\033[0;31m%lu %d is eating\033[0m\n", philo->timestamp,
			philo->id);
	if (whattodo == TAKE_FORK)
		printf("\033[0;35m%lu %d has taken a fork\033[0m\n", philo->timestamp,
			philo->id);
	if (whattodo == SLEEP)
		printf("\033[0;36m%lu %d is sleeping\033[0m\n", philo->timestamp,
			philo->id);
	if (whattodo == THINK)
		printf("\033[0;33m%lu %d is thinking\033[0m\n", philo->timestamp,
			philo->id);
	if (whattodo == DIE)
		printf("\033[0;32m%lu %d died\033[0m\n", philo->timestamp,
			philo->id);
}		

// Check if philo starved. lock game state, and print action.
int	ft_do(t_philo *philo, unsigned long time_to, int whattodo)
{
	int	err;

	err = 0;
	err = philo_starved(philo);
	err = pthread_mutex_lock(&philo->diner->game_over_lock);
	if (!philo->diner->game_over)
		color_print(philo, whattodo);
	err = pthread_mutex_unlock(&philo->diner->game_over_lock);
	philo->timestamp += time_to;
	wait_until(philo->timestamp, 0);
	return (err);
}

// Philo grabs forks (and wait as long as they have to).
// When forks are in hands, save time of last meal.
// 
int	philo_eats(t_philo *philo)
{
	int	err;

	err = grab_forks(philo);
	philo->last_eat = philo->timestamp;
	err = ft_do(philo, philo->diner->set.time_to_eat, EAT);
	err = drop_forks(philo);
	philo->n_meals++;
	return (err);
}

int	philo_sleeps(t_philo *philo)
{
	int	err;

	err = ft_do(philo, philo->diner->set.time_to_sleep, SLEEP);
	return (err);
}

int	philo_thinks(t_philo *philo)
{
	int	err;

	err = ft_do(philo, 0, THINK);
	return (err);
}
