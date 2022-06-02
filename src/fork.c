/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:37:35 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/02 12:41:02 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	tries(t_philo *philos, t_fork fork)
{
	int	err;
	int	fork_is_free;

	fork_is_free = 0;
	pthread_mutex_lock(&fork.fork_is_taken);
	if (!fork.fork_id)
	{
		fork.fork_id = philos->id;
		fork_is_free = 1;
	}
	pthread_mutex_unlock(&fork.fork_is_taken);
	err = 0;
	if (fork_is_free)
		err = ft_do(philos, 0, TAKE_FORK);
	if (err)
		return (-1);
	return (fork_is_free);
}

void	add_waited_time(t_philo *philos,
	unsigned long *time_waited)
{
	(*time_waited) = elapsed_time_since_start(philos) + (*time_waited);
	philos->timestamp = (*time_waited);
}

int grab_fork(t_philo *philos, t_fork fork)
{
	int	fork_is_free;
	unsigned long time_waited;
	
	time_waited = 0;
	fork_is_free = tries(philos, fork);
	// printf("%d\n", fork_is_free);
	if (fork_is_free)
		return (0);
	if (fork_is_free == -1)
		return (-1);
	else if (!fork_is_free)
	{
		puts("yo");
		add_waited_time(philos, &time_waited);
		grab_fork(philos, fork);
	}
	return (0);
}

// int	grab_fork(t_philo *philos, t_fork fork)
// {
// 	int	fork_is_free;
// 	unsigned long time_waited;
	
// 	time_waited = 0;
// 	fork_is_free = 0;
// 	while (!fork_is_free)
// 	{
// 		fork_is_free = tries(philos, fork);
// 		if (fork_is_free == -1)
// 			return (-1);
// 		else if (!fork_is_free)
// 		{
// 			puts("YO");
// 			add_waited_time(philos, &time_waited);			
// 		}
// 	}
// 	return (0);
// }

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

int	drop_fork(t_fork fork)
{	
	int	err;
	
	err = pthread_mutex_lock(&fork.fork_is_taken);
	fork.fork_id = 0;
	err = pthread_mutex_unlock(&fork.fork_is_taken);
	return (err);
}

int	drop_forks(t_philo *philos)
{
	int	err;
	err = drop_fork(philos->left_fork);
	err = drop_fork(philos->right_fork);
	return (err);
}
