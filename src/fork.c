/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork->c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:37:35 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/02 14:56:09 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

static void	wait_before_new_try(t_philo *philos, unsigned long *time_waited)
{
	unsigned long	new_try;

	new_try = philos->timestamp + 0.2;
	ft_wait_until(new_try, 0);
	*time_waited += 0.2;
	if (*time_waited > 1000)
	{
		*time_waited = 0;
		philos->timestamp++;
	}
}

int	tries(t_philo *philos, t_fork *fork)
{
	int	err;
	int	fork_is_free;

	if (!fork)
		return (-1);
	fork_is_free = 0;
	pthread_mutex_lock(&fork->fork_is_taken);
	if (!fork->fork_id)
	{
		// printf("fork_id = %d\n", fork->fork_id);
		fork->fork_id = philos->id;
		fork_is_free = 1;
	}
	pthread_mutex_unlock(&fork->fork_is_taken);
	// printf("fork_id = %d\n", fork->fork_id);
	err = 0;
	if (fork_is_free)
		err = ft_do(philos, 0, TAKE_FORK);
	if (err)
		return (-1);
	return (fork_is_free);
}

int	grab_fork(t_philo *philos, t_fork *fork)
{
	int	is_fork_taken;
	unsigned long	time_waited;
	int	end;

	is_fork_taken = 0;
	time_waited = 0;
	while (!is_fork_taken)
	{
		end = !kill_philo_if_he_starved(philos);
		if (end)
			return (0);
		is_fork_taken = tries(philos, fork);
		// printf("is fork taken %d\n", is_fork_taken);
		if (is_fork_taken == -1)
			return (1);
		if (!is_fork_taken)
			wait_before_new_try(philos, &time_waited);
	}
	return (0);
}

int	grab_forks(t_philo *philos)
{
	int	err;
	
	// printf("did philo starved? %d\n", kill_philo_if_he_starved(philos));
	// if (!kill_philo_if_he_starved(philos))
	// 	return (0);
	err = grab_fork(philos, philos->right_fork);
	err = grab_fork(philos, philos->left_fork);
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

int	drop_forks(t_philo *philos)
{
	int	err;

	err = drop_fork(philos->left_fork);
	err = drop_fork(philos->right_fork);
	return (err);
}
