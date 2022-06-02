/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:35:27 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/02 19:18:29 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//initialize id, when last_meal was, number of meals eaten and pointer to
//state for each philosopher.
void init_philo(t_philo *philo, int id, t_game *state)
{
	philo->id = id;
	// printf("id : %d\n", philo->id);
	philo->last_eat = -1;
	// printf("last_eat : %ld\n", philo->last_eat);
	philo->n_meals = 0;
	// printf("n_meals : %d\n", philo->n_meals);
	philo->state = state;
	// printf("philo->state : %d\n", philo->state);
	philo->right_fork = 0;
	philo->left_fork = 0;
}

//creating as many t_philo structures as there are philos
int	init_game(t_philo *philos, t_game *state)
{
	int	id;

	id = 0;
	// printf("%d\n", state->set.n_philos);
	while (id < state->set.n_philos)
	{
		init_philo(&philos[id], id + 1, state);
		// printf("%d\n", philos[id].id);
		id++;
	}
	if (init_forks(philos, state->set) == MUTEX_FAIL)
		return (MUTEX_FAIL);
	return (0);
}

int ft_quit(t_philo *philos, int err)
{
	free(philos);
	return(err);
}

int	main(int argc, char **argv)
{
	t_philo				*philos;
	t_game				*state;
	int					err;
	
	err = 0;
	state = malloc(sizeof(t_game));
	if (!state)
		return (1);
	philos = malloc(sizeof(t_philo) * (ft_atoi(argv[1])));
	if (!philos)
		ft_panic(MALLOC_FAILURE);
	if (argc == 5 || argc == 6)
		err = ft_parse(argc, argv, state);
	else 
		err = ft_panic(WRONG_NARG);
	if (err != 0)
		return (ft_quit(philos, err));
	err = init_game(philos, state);
	if (err != 0)
		return (ft_quit(philos, err));
	err = init_end_game(state);
	if (err != 0)
		return (ft_quit(philos, err));
	// err = init_printf_lock(philos);
	// if (err != 0)
	// 	return (ft_quit(philos, err));
	err = start_simulation(philos, state);
	if (err != 0)
		return (ft_quit(philos, err));
	return (0);
}