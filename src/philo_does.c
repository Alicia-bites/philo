/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_does.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:49:43 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/31 15:12:44 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

// int	can_eat(t_philo *philos)
// {
// 	if (philo_grabs_fork(philos));
// 		return (1);
// 	return (0);
// }

void	philo_eats(t_philo *philos)
{
	// if (can_eat(philos))
	printf("%ld %d is eating\n", philos->timestamp, philos->id);
	philos->last_eat = philos->timestamp;
	philos->timestamp += philos->state.set.time_to_sleep;
	printf("n_meals for %d = %d\n", philos->id, philos->n_meals++);
}

void	philo_sleeps(t_philo *philos)
{
	printf("%ld %d is sleeping\n", philos->timestamp, philos->id);
	// printf("before : %ld\n", philos->timestamp);
	philos->timestamp += philos->state.set.time_to_sleep;
	// printf("after : %ld\n", philos->timestamp);
}

void	philo_thinks(t_philo *philos)
{
	printf("%ld %d is thinking\n", philos->timestamp, philos->id);
}