/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:37:07 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/01 16:11:19 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	game_is_over(t_philo *philos)
{
	// printf("n meals %d\n", philos->n_meals);
	// printf("n meals %d\n", philos->state.set->n_meals);
	if (philos->n_meals != -1 && philos->n_meals == philos->state.set.n_meals)
		return (1);
	return (0);
}

unsigned long	get_starting_time(t_philo *philos)
{
	struct timeval	start;
	
	gettimeofday(&start, 0);
	// printf("%ld\n", start.tv_sec);
	// printf("%ld\n", start.tv_usec);
	// printf("%ld\n", philos->starting_time = (start.tv_sec * 1000)
	// 	+ (start.tv_usec / 1000));
	return (philos->starting_time = (start.tv_sec * 1000)
		+ (start.tv_usec / 1000));
}

int	wait_to_eat(t_philo *philos)
{
	unsigned long	next_meal;

	if (philos->state.set.n_philos % 2 != 1)
	{
		if (philos->last_eat == (unsigned long) -1)
			philos->last_eat = 0;
		return ;
	}
	if (philos->last_eat == (unsigned long) -1)
	{
		if (philos->id == philos->state.set.n_philos)
			next_meal = 0;
		else if (philos->id % 2 == 0)
			next_meal = philos->state.set.time_to_eat;
		else
			next_meal = philos->state.set.time_to_eat * 2;
	}
	else
		next_meal = philos->last_eat * philos->state.set.time_to_eat;
	philos->timestamp = next_meal;
}
	
void	*sim(void *param)
{
	t_philo *philo;
	philo = (t_philo *)param;
	// printf("is game over? %d\n", game_is_over(philo));
	while (!game_is_over(philo))
	{
		wait_to_eat(philo);
		philo_eats(philo);
		philo_sleeps(philo);
		philo_thinks(philo);
	}
	return (0);
}

int	start_simulation(t_philo *philos, t_game state)
{
	int	i;
	int err;

	i = 0;
	philos->starting_time = get_starting_time(philos);
	// printf("%lu\n", philos->starting_time);
	// printf("n philo = %d\n", state.set.n_philos);
	while (i < state.set.n_philos)
	{
		err = pthread_create(&philos[i].thread, 0, &sim, &philos[i]);
		// printf("err = %d\n", err);
		if (err != 0)
			return (ft_panic(THREAD_ERROR));
		i++;
	}
	i = 0;
	while (i < state.set.n_philos)
	{
		pthread_join(philos[i].thread, 0);
		i++;
	}
	return (0);
}