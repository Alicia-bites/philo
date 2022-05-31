/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:01:45 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/31 15:42:07 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

// int	wait(t_philo *philos)
// {
// 	return (0);
// }

// int	try(t_philo *philos, t_fork *fork)
// {
// 	return (0);
// }

// int	philo_grabs_fork(t_philo *philos)
// {
// 	// int	can_eat;

// 	// can_eat = try(philos, philos->right_fork);
// 	// can_eat = try(philos, philos->left_fork);
// 	// if (can_eat)
// 	// 	return (1);
// 	// // else
// 	// // 	// wait(philos);
// 	return (0);
// }

t_fork	init_fork(void)
{
	t_fork	fork;

	fork.fork_id = 0;
	if (pthread_mutex_init(&fork.fork_is_taken, 0))
		fork.fork_id = -1;
	return (fork);
}

int	give_fork_to_philos(t_philo left_philo, t_philo right_philo)
{
	left_philo.left_fork = init_fork();
	if (left_philo.left_fork.fork_id == -1)
		return (MUTEX_FAIL);
	left_philo.left_fork = right_philo.right_fork;
	return (left_philo.id + right_philo.id);
}

int	init_forks(t_philo *philos, t_settings set)
{
	int				i;
	t_philo			left_philo;

	i = 0;
	printf("%d\n", set.n_philos);
	while (i < set.n_philos)
	{
		if (i == 0 && set.n_philos > 1)
			left_philo = philos[set.n_philos -1];
		else if (set.n_philos > 1)
			left_philo = philos[i - 1];
		printf("left_philo = %d\n", left_philo.id);
		printf("right_philo = %d\n", philos[i].id);
		puts("---------------------------------------------------------------");
		if (give_fork_to_philos(left_philo, philos[i]) == MUTEX_FAIL)
			return (MUTEX_FAIL);
		i++;
	}
	return (0);
}