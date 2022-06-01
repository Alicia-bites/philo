/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:37:07 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/01 17:55:48 by amarchan         ###   ########.fr       */
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

struct timeval	ft_convert(unsigned long moment_ms)
{
	struct timeval	moment_converted;

	moment_converted.tv_sec = moment_ms / 1000;
	moment_converted.tv_usec = moment_ms % 1000 * 1000;
	return (moment_converted);
}

int	is_greater_than(unsigned long a, unsigned long b)
{
	if (a > b)
		return (1);
	return (0);
}

unsigned long	time_diff(struct timeval a, struct timeval b)
{
	unsigned long	a_long;
	unsigned long	b_long;

	a_long = a.tv_sec * 1000 + a.tv_usec / 1000;
	b_long = b.tv_sec * 1000 + b.tv_usec / 1000;
	return (a_long - b_long);
}

//make philo wait until moment_ms
void	ft_wait_until(unsigned long moment_ms, struct timeval *time_ref)
{
	static struct timeval	static_time_ref;
	struct	timeval			moment;
	struct timeval			now;
	unsigned long			static_time_ref_long;

	moment = ft_convert(moment_ms);
	if (time_ref)
		static_time_ref = *time_ref;
	gettimeofday(&now, 0);
	static_time_ref_long = static_time_ref.tv_sec
		* 1000 + static_time_ref.tv_usec / 1000;
	while (!is_greater_than(time_diff(now, moment), static_time_ref_long))
	{
		usleep(10);
		gettimeofday(&now, 0);
	}
}

unsigned long	when_is_next_meal(t_philo *philos)
{
	unsigned long next_meal;
	
	if (philos->state.set.n_philos % 2 != 1)
	{
		if (philos->last_eat == (unsigned long) -1)
			philos->last_eat = 0;
		return (0);
	}
	if (philos->last_eat == (unsigned long) -1)
	{
		if (philos->id == philos->state.set.n_philos)
			return (next_meal = 0);
		else if (philos->id % 2 == 0)
			return (next_meal = philos->state.set.time_to_eat);
		else
			return (next_meal = philos->state.set.time_to_eat * 2);
	}
	else
		return (next_meal = philos->last_eat * philos->state.set.time_to_eat);
	return (0);
}

void	wait_to_eat(t_philo *philos)
{
	unsigned long	next_meal;
	
	next_meal = when_is_next_meal(philos);
	ft_wait_until(next_meal, 0);
	philos->timestamp = next_meal;
}

static void	wait_if_even_nb_of_philo(t_philo *philos)
{
	if (!(philos->id % 2))
	{
		philos->timestamp += philos->state.set.time_to_eat / 2;
		ft_wait_until(philos->timestamp, 0);
	}
}
	
void	*sim(void *param)
{
	t_philo *philo;
	philo = (t_philo *)param;
	wait_if_even_nb_of_philo(philo);
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