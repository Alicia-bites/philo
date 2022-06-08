/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:05:04 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/08 13:27:11 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	ft_panic(int errcode)
{
	if (errcode == NO_PHILO || errcode == NO_MEALS)
		return (errcode);
	printf("Error !\n");
	if (errcode == WRONG_NARG)
		printf("Usage :./philo number_of_philosophers time_to_die " \
		"time_to_eat " \
		"time_to_sleep [number_of_times_each_philosopher_must_eat].\n");
	else if (errcode == WRONG_ARG)
		printf("Argument is univalid.\n");
	else if (errcode == NOT_INT)
		printf("Argument is not an integer.\n");
	else if (errcode == OUT_INT)
		printf("Out of boundaries.\n");
	else if (errcode == EMPTY_STR)
		printf("Found empty string\n");
	else if (errcode == MALLOC_FAILURE)
		printf("Memory allocation failed.\n");
	else if (errcode == MUTEX_FAILURE)
		printf("Failed to init or lock mutex.\n");
	else if (errcode == INT_NEG)
		printf("Argument can't be negative.\n");
	return (errcode);
}

//check if argument isn't smaller than INT_MIN or bigger than INT_MAX
static int	ft_invalid_int(long long arg)
{
	return (!(arg <= INT_MAX && arg >= INT_MIN));
}

//check if arguments are correct and if so returns 1
char	**check_args(int argc, char **argv, int *err)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!isinteger(argv[i]))
		{
			*err = NOT_INT;
			return (argv);
		}
		if (ft_atoll(argv[i]) < 0)
			*err = INT_NEG;
		ft_strip(argv[i]);
		if (ft_strlen(argv[i]) == 0)
			*err = EMPTY_STR;
		if (ft_strlen(argv[i]) <= 11)
		{
			if (ft_invalid_int(ft_atoll(argv[i])))
				*err = OUT_INT;
		}
		else
			*err = NOT_INT;
		i++;
	}
	return (argv);
}

int	ft_parse(int argc, char **argv, t_game *diner)
{
	int	err;

	err = 0;
	argv = check_args(argc, argv, &err);
	if (err != 0)
		return (err);
	diner->set.n_philos = ft_atoi(argv[1]);
	diner->set.time_to_die = ft_atoi(argv[2]);
	diner->set.time_to_eat = ft_atoi(argv[3]);
	diner->set.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		diner->set.n_meals = ft_atoi(argv[5]);
	else
		diner->set.n_meals = -1;
	return (0);
}
