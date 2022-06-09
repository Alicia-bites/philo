/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 13:30:40 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/09 10:45:02 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	tries(t_philo *philo, t_fork *fork)
{
	int	err;
	int	fork_is_free;

	if (!fork)
		return (-1);
	fork_is_free = 0;
	pthread_mutex_lock(&fork->fork_is_taken);
	if (!fork->fork_id)
	{
		fork->fork_id = philo->id;
		fork_is_free = 1;
	}
	pthread_mutex_unlock(&fork->fork_is_taken);
	err = 0;
	if (fork_is_free)
		err = ft_do(philo, 0, TAKE_FORK);
	if (err)
		return (-1);
	return (fork_is_free);
}

int	grab_fork(t_philo *philo, t_fork *fork)
{
	int				is_fork_taken;
	double			time_waited;

	is_fork_taken = 0;
	time_waited = 0;
	while (!is_fork_taken)
	{
		if (philo_starved(philo))
			return (0);
		is_fork_taken = tries(philo, fork);
		if (is_fork_taken == -1)
			return (1);
		if (!is_fork_taken)
			wait_and_add_waited_time(philo, &time_waited);
	}
	return (0);
}

int	grab_forks(t_philo *philo)
{
	int	err;

	err = grab_fork(philo, philo->right_fork);
	err = grab_fork(philo, philo->left_fork);
	return (err);
}

int	drop_fork(t_fork *fork)
{	
	int	err;

	if (!fork)
		return (0);
	err = pthread_mutex_lock(&fork->fork_is_taken);
	fork->fork_id = 0;
	err = pthread_mutex_unlock(&fork->fork_is_taken);
	return (err);
}

int	drop_forks(t_philo *philo)
{
	int	err;

	err = drop_fork(philo->left_fork);
	err = drop_fork(philo->right_fork);
	return (err);
}
