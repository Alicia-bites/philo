/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 13:26:24 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/09 11:05:50 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

//creates a new fork
t_fork	*new_fork(int *has_failed)
{	
	t_fork			*fork;

	fork = malloc(sizeof(t_fork));
	if (!fork)
		return (0);
	fork->fork_id = 0;
	*has_failed = pthread_mutex_init(&fork->fork_is_taken, 0);
	if (*has_failed)
	{
		free(fork);
		return (0);
	}
	return (fork);
}

//give one fork for 2 philososphers. One fork is "between" 2 philo.
int	give_fork_to_philos(t_philo *left_philo, t_philo *right_philo)
{
	int	has_failed;

	has_failed = 0;
	left_philo->left_fork = new_fork(&has_failed);
	if (has_failed)
		return (MUTEX_FAILURE);
	if (!left_philo->left_fork)
		return (MALLOC_FAILURE);
	right_philo->right_fork = left_philo->left_fork;
	return (0);
}

//if there are more than one philo, deal forks to philosophers
//if there is just one philo, is takes a fork and then die at time_to_die ms
int	deal_forks(t_philo *philos, t_settings *set, int time_to_die)
{
	int		i;
	int		err;
	t_philo	*left_philo;

	i = 0;
	err = 0;
	left_philo = 0;
	while (i < set->n_philos && set->n_philos > 1)
	{
		if (i == 0)
			left_philo = &philos[set->n_philos - 1];
		else
			left_philo = &philos[i - 1];
		err = give_fork_to_philos(left_philo, &philos[i]);
		if (err)
			return (ft_panic(err));
		i++;
	}
	if (set->n_philos == 1)
	{
		printf("\033[0;35m%d %d has taken a fork\033[0m\n", 0, 1);
		printf("\033[0;32m%d %d died\033[0m\n", time_to_die, 1);
		return (1);
	}
	return (0);
}
