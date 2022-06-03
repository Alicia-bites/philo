/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:05:04 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/03 15:01:24 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

int	ft_panic(int errcode)
{
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
char **check_args(int argc, char **argv, int *err)
{
	int	i;
	
	i = 1;
	while (i < argc)
	{
		if (!isinteger(argv[i]))
		{
			*err = ft_panic(NOT_INT);
			return (argv);			
		}
		if (ft_atoll(argv[i]) < 0)
			*err = ft_panic(INT_NEG);
		ft_strip(argv[i]);
		if (ft_strlen(argv[i]) == 0)
			*err = ft_panic(EMPTY_STR);
		else if (ft_strlen(argv[i]) <= 11 && isinteger(argv[i]))
		{
			if (ft_invalid_int(ft_atoll(argv[i])))
				*err = ft_panic(OUT_INT);
		}
		// else 
		// {
		// 	*err = ft_panic(NOT_INT);
		// 	printf("err = %d\n", *err);			
		// }
		i++;
	}
	return (argv);
}

int ft_parse(int argc, char **argv, t_game *state)
{   
	int	err;
	
	err = 0;
    argv = check_args(argc, argv, &err);
	if (err != 0)
		return (err);
    state->set.n_philos = ft_atoi(argv[1]);
    // printf("n_philos : %d\n", state->set.n_philos);
    state->set.time_to_die = ft_atoi(argv[2]);
    // printf("time_to_die : %d\n", state->set.time_to_die);
    state->set.time_to_eat = ft_atoi(argv[3]);
    // printf("time_to_eat : %d\n", state->set.time_to_eat);
    state->set.time_to_sleep = ft_atoi(argv[4]);
    // printf("time_to_sleep : %d\n", state->set.time_to_sleep);
    if (argc == 6)
    {
        state->set.n_meals = ft_atoi(argv[5]);
        // printf("n_meals : %d\n", state->set.n_meals);        
    }
    else
	{
        state->set.n_meals = -1;		
	}
	return (0);
}
