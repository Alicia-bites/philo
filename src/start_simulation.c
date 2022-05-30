/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:37:07 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/28 14:21:55 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*sim(void *param)
{
	t_philo *philo;

	philo = (t_philo *)param;
	
	
}

void	start_simulation(t_philo *philos, t_game *state)
{
	int	i;

	i = 0;
	while (i < state->set.n_philos)
	{
		if (pthread_create(&philos[i].thread, 0, &sim, &philos[i]) == NULL)
			ft_panic(THREAD_ERROR);
		i++;
	}
}