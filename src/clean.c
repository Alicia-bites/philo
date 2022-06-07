/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:16:02 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/07 14:43:44 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_forks(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].diner->set.n_philos)
	{
		free(philos[i].left_fork);
		i++;
	}
}

int	ft_clean(t_philo *philos, t_game *diner, int err)
{
	if (diner)
		free(diner);
	if (philos)
		free(philos);
	return (err);
}

int	ft_clean_with_forks(t_philo *philos, t_game *diner, int err)
{
	if (philos->right_fork && philos->left_fork)
		free_forks(philos);
	if (diner)
		free(diner);
	if (philos)
		free(philos);
	return (err);
}
