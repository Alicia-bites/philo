/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:37:07 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/30 18:03:54 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	can_eat(t_philo *philos)
{
	if (philos->right_fork.fork_id && philos->left_fork.fork_id)
		return (1);
	return (0);
}

void	philo_eats(t_philo *philos)
{
	if (can_eat(philos))
		printf("%ld %d is eating", philos->timestamp, philos->id);
	philos->last_eat = philos->timestamp;
	philos->timestamp += philos->state->set->time_to_sleep;
}

void	philo_sleeps(t_philo *philos)
{
	printf("%ld %d is sleeping\n", philos->timestamp, philos->id);
	printf("before : %ld\n", philos->timestamp);
	philos->timestamp += philos->state->set->time_to_sleep;
	printf("after : %ld\n", philos->timestamp);
}

void	philo_thinks(t_philo *philos)
{
	printf("%ld %d is thinking\n", philos->timestamp, philos->id);
}

int	sim_is_over(t_philo *philos)
{
	if (philos->n_meals != -1 && philos->n_meals == philos->state->set->n_meals)
		return (1);
	return (0);
}

void	set_start_time(t_philo *philos)
{
	struct timeval	start;
	
	gettimeofday(&start, 0);
	// printf("ref_time : %ld s\n", starting_time.tv_sec);
	// printf("ref_time : %ld ms\n", starting_time.tv_usec);
	philos->starting_time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	printf("now : %ld ms\n", philos->starting_time);
}

void	*sim(void *param)
{
	t_philo *philo;
	philo = (t_philo *)param;
	while (!sim_is_over(philo))
	{
		philo_eats(philo);
		philo_sleeps(philo);
		philo_thinks(philo);
	}
	printf("sim\n");
	return (0);
}

void	start_simulation(t_philo *philos, t_game *state)
{
	int	i;
	int err;

	i = 0;
	set_start_time(philos);
	while (i < state->set->n_philos)
	{
		err = pthread_create(&philos[i].thread, 0, &sim, &philos[i]);
		printf("err = %d\n", err);
		if (err == 0)
			ft_panic(THREAD_ERROR);
		i++;
	}
}