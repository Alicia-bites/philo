/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:16:02 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/08 11:53:54 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_forks(t_philo *philos_list)
{
	int	i;

	i = 0;
	while (i < philos_list[0].diner->set.n_philos)
	{
		free(philos_list[i].left_fork);
		i++;
	}
}

int	ft_clean(t_philo *philos_list, t_game *diner, int err)
{
	ft_panic(err);
	if (diner)
		free(diner);
	if (philos_list)
		free(philos_list);
	return (err);
}

int	ft_clean_with_forks(t_philo *philos_list, t_game *diner, int err)
{
	if (err)
		ft_panic(err);
	if (philos_list->right_fork && philos_list->left_fork)
		free_forks(philos_list);
	if (diner)
		free(diner);
	if (philos_list)
		free(philos_list);
	return (err);
}
