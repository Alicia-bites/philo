/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_does.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:49:43 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/07 14:43:44 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	ft_print(t_philo *philo, char *whattodo)
{
	int	err;

	err = 0;
	printf("%lu %d %s\n", philo->timestamp, philo->id, whattodo);
	return (err);
}

int	ft_do(t_philo *philo, unsigned long time_to, char *whattodo)
{
	int	err;

	err = 0;
	err = philo_starved(philo);
	err = pthread_mutex_lock(&philo->diner->game_over_lock);
	if (!philo->diner->game_over)
		ft_print(philo, whattodo);
	err = pthread_mutex_unlock(&philo->diner->game_over_lock);
	philo->timestamp += time_to;
	wait_until(philo->timestamp, 0);
	return (err);
}

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
