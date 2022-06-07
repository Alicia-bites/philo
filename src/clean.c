/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:16:02 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/07 13:25:35 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_forks(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].state->set.n_philos)
	{
		free(philos[i].left_fork);
		i++;
	}
}

int	ft_clean(t_philo *philos, t_game *state, int err)
{
	if (state)
		free(state);
	if (philos)
		free(philos);
	return (err);
}

int	ft_clean_with_forks(t_philo *philos, t_game *state, int err)
{
	if (philos->right_fork && philos->left_fork)
		free_forks(philos);
	if (state)
		free(state);
	if (philos)
		free(philos);
	return (err);
}
