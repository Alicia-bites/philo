/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_does.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:49:43 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/01 18:00:10 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int kill_philo_if_he_starved(t_philo *philos)
{
	int err;

	err = 0;
	// printf("hellooo\n");
	printf("timestamp : %lu\n", philos->timestamp);
	printf("last_eat : %d\n", (int)philos->last_eat);
	// printf("%d\n", (philos->last_eat + philos->state.set.time_to_die) > philos->timestamp);
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

int ft_do(t_philo *philos, unsigned long time_to, char *whattodo)
{
	int err;

	err = 0;
	// err = kill_philo_if_he_starved(philos);
	if (!philos->state.game_over)
		printf("%ld %d %s\n", philos->timestamp, philos->id, whattodo);
	philos->timestamp += time_to;
	return (0);
}

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

//evaluate elapsed time since program started
unsigned long	elapsed_time(t_philo *philos)
{
	struct timeval	now;
	unsigned long	new_time;
	
	gettimeofday(&now, 0);
	new_time = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	new_time -= philos->starting_time;
	return (new_time);
}

void	add_waited_time(t_philo *philos,
	unsigned long *time_waited)
{
	(*time_waited) = elapsed_time(philos) + (*time_waited);
	philos->timestamp = elapsed_time(philos) + (*time_waited);
}

int grab_fork(t_philo *philos, t_fork fork)
{
	int	fork_is_free;
	unsigned long time_waited;
	
	// puts("yo");
	time_waited = 0;
	fork_is_free = tries(philos, fork);
	if (fork_is_free)
		return (0);
	if (fork_is_free == -1)
		return (-1);
	else if (!fork_is_free)
	{
		grab_fork(philos, fork);
		add_waited_time(philos, &time_waited);
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
// 			add_waited_time(philos, &time_waited);
// 	}
// 	return (0);
// }

int	grab_forks(t_philo *philos)
{
	int	err;
	
	// printf("did philo starved? %d\n", kill_philo_if_he_starved(philos));
	// if (!kill_philo_if_he_starved(philos))
	// 	return (0);
	// printf("hellooo\n");
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

int	philo_eats(t_philo *philos)
{
	int	err;

	err = grab_forks(philos);
	philos->last_eat = philos->timestamp;
	err = ft_do(philos, philos->state.set.time_to_eat, EAT);
	philos->timestamp += philos->state.set.time_to_eat;
	err = drop_forks(philos);
	philos->n_meals++;
	// printf("n_meals for %d = %d\n", philos->id, philos->n_meals++);
	return (err);
}

int	philo_sleeps(t_philo *philos)
{
	int	err;
	
	err = ft_do(philos, philos->state.set.time_to_sleep, SLEEP);
	return (err);
}

int	philo_thinks(t_philo *philos)
{
	int	err;
	
	err = ft_do(philos, 0, THINK);
	return (err);
}