/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:35:27 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/06 12:39:15 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//initialize id, when last_meal was, number of meals eaten and pointer to
//state for each philosopher.
void init_philo(t_philo *philo, int id, t_game *state)
{
	philo->id = id;
	philo->last_eat = -1;
	philo->n_meals = 0;
	philo->state = state;
	philo->right_fork = 0;
	philo->left_fork = 0;
	philo->timestamp = 0;
}

//Create as many t_philo structures as there are philos.
// If no n_philos = 0 (no philosophers), return.
int	init_game(t_philo *philos_list, t_game *state)
{
	int	id;
	int	err;

	id = 0;
	err = 0;
	if (state->set.n_philos == 0)
		return (NO_PHILO);
	while (id < state->set.n_philos)
	{
		init_philo(&philos_list[id], id + 1, state);
		id++;
	}
	if (deal_forks(philos_list, &state->set))
		return (err);
	err = init_printf_lock(philos_list);
	err = init_end_game(state);
	err = start_simulation(philos_list, state);
	return (err);
}

int	main(int argc, char **argv)
{
	t_philo				*philos_list;
	t_game				*state;
	int					err;
	
	err = 0;
	if (argc != 5 && argc != 6)
		return (ft_panic(WRONG_NARG));
	state = malloc(sizeof(t_game));
	if (!state)
		return (1);
	philos_list = malloc(sizeof(t_philo) * (ft_atoi(argv[1])));
	if (!philos_list)
		ft_panic(MALLOC_FAILURE);
	if (argc == 5 || argc == 6)
		err = ft_parse(argc, argv, state);
	if (err != 0)
		return (ft_clean(philos_list, state, err));
	err = init_game(philos_list, state);
	if (err)
	{
		ft_panic(err);
		return (ft_clean(philos_list, state, err));		
	}
	return (ft_clean_with_forks(philos_list, state, err));
}