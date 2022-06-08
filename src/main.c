/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:35:27 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/08 15:26:30 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

// Initialize id, when last_meal was, number of meals eaten and pointer to
// diner for each philosopher.
void	init_philo(t_philo *philo, int id, t_game *diner)
{
	philo->id = id;
	philo->last_eat = -1;
	philo->n_meals = 0;
	philo->diner = diner;
	philo->right_fork = 0;
	philo->left_fork = 0;
	philo->timestamp = 0;
}

// Create as many t_philo structures as there are philos.
// If no n_philos = 0 (no philosophers), return.
int	init_game(t_philo *philos_list, t_game *diner)
{
	int	id;
	int	err;

	id = 0;
	err = 0;
	if (diner->set.n_philos == 0)
		return (NO_PHILO);
	if (diner->set.n_meals == 0)
		return (NO_MEALS);
	while (id < diner->set.n_philos)
	{
		init_philo(&philos_list[id], id + 1, diner);
		id++;
	}
	if (deal_forks(philos_list, &diner->set))
		return (err);
	err = init_end_game(diner);
	err = start_diner(philos_list, diner);
	return (err);
}

int	main(int argc, char **argv)
{
	t_philo				*philos_list;
	t_game				*diner;
	int					err;

	err = 0;
	if (argc != 5 && argc != 6)
		return (ft_panic(WRONG_NARG));
	diner = malloc(sizeof(t_game));
	if (!diner)
		return (ft_panic(MALLOC_FAILURE));
	philos_list = malloc(sizeof(t_philo) * (ft_atoi(argv[1])));
	if (!philos_list)
		return (ft_clean(philos_list, diner, MALLOC_FAILURE));
	if (argc == 5 || argc == 6)
		err = ft_parse(argc, argv, diner);
	if (err != 0)
		return (ft_clean(philos_list, diner, err));
	err = init_game(philos_list, diner);
	if (err)
		return (ft_clean(philos_list, diner, err));
	return (ft_clean_with_forks(philos_list, diner, err));
}
