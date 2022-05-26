/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:35:27 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/26 13:52:41 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philo *philo, int id, t_game *state)
{
	philo->id = id;
	printf("%d\n", philo->id);
	philo->last_eat = -1;
	printf("%ld\n", philo->last_eat);
	philo->n_meals = 0;
	printf("%d\n", philo->n_meals);
	philo->state = state;
	printf("%p\n", philo->state);
}

//creating as many t_philo structures as there are philos
int	init_game()
{
	t_philo	*philos;
	t_game	*state;
	int	id;

	id = 0;
	philos = NULL;
	state = NULL;
	state = malloc(sizeof(t_game));
	if (!state)
		ft_panic(MALLOC_FAILURE);
	philos = malloc(sizeof(t_philo) * state->set.n_philos);
	if (!philos)
		ft_panic(MALLOC_FAILURE);
	while (id < state->set.n_philos)
	{
		init_philo(philos, id + 1, state);
		id++;
	}
	return (0);
}

int	main(int argc, char **argv)
{	
	if (argc == 5 || argc == 6)
		ft_parse(argc, argv);
	else
		ft_panic(WRONG_NARG);
	init_game();
	return (0);
}