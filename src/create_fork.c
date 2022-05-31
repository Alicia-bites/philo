/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 11:01:45 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/31 17:13:25 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

t_fork	create_fork(void)
{
	t_fork		fork;
	
	fork.fork_id = 0;
	if (pthread_mutex_init(&fork.fork_is_taken, 0))
		fork.fork_id = -1;
	return (fork);
}

int	give_fork_to_philos(t_philo left_philo, t_philo right_philo)
{
	left_philo.left_fork = create_fork();
	// printf("left philo, left fork ID : %d\n", left_philo.left_fork.fork_id);
	if (left_philo.left_fork.fork_id == -1)
		return(ft_panic(MUTEX_FAIL));
	right_philo.right_fork = left_philo.left_fork;
	right_philo.right_fork.fork_id = left_philo.left_fork.fork_id;
	// printf("right philo, right fork ID : %d\n", right_philo.right_fork.fork_id);
	return (0);
}

int	init_forks(t_philo *philos, t_settings set)
{
	int		i;
	t_philo	left_philo;

	i = 0;
	while (i < set.n_philos)
	{
		if (i == 0 && set.n_philos > 1)
			left_philo = philos[set.n_philos -1];
		else if (set.n_philos > 1)
			left_philo = philos[i - 1];
		// printf("left_philo = %d\n", left_philo.id);
		// printf("right_philo = %d\n", philos[i].id);
		// puts("---------------------------------------------------------------");
		if (give_fork_to_philos(left_philo, philos[i]) == MUTEX_FAIL)
			return (MUTEX_FAIL);
		i++;
	}
	return (0);
}