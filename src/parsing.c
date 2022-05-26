/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:05:04 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/26 13:54:04 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"
#include "../ft_printf/ft_printf.h"

void	ft_panic(int errcode)
{
	ft_printf("Error !\n");
	if (errcode == WRONG_NARG)
		ft_printf("Usage :./philo number_of_philosophers time_to_die " \
		"time_to_eat " \
		"time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	else if (errcode == WRONG_ARG)
		ft_printf("Argument is univalid");
	else if (errcode == MALLOC_FAILURE)
		ft_printf("Memory allocation failed\n");
	exit(errcode);
}

//check if argument isn't smaller than INT_MIN or bigger than INT_MAX
static int	ft_invalid_int(long long arg)
{
	return (!(arg <= INT_MAX && arg >= INT_MIN));
}

//check if arguments are correct and if so returns 1
char **check_args(int argc, char **argv)
{
	int	i;
	
	i = 1;
	while (i < argc)
	{
		ft_strip(argv[i]);
		if (ft_strlen(argv[i]) == 0)
			ft_panic(EMPTY_STR);
		else if (ft_strlen(argv[i]) <= 11 && isinteger(argv[i]))
		{
			if (ft_invalid_int(ft_atoll(argv[i])))
				ft_panic(OUT_INT);
		}
		i++;
	}
	return (argv);
}

int	ft_parse(int argc, char **argv)
{
	t_settings	*set;
	
	set = NULL;
	set = malloc(sizeof(t_settings));
	if (!set)
		ft_panic(MALLOC_FAILURE);
	argv = check_args(argc, argv);
	ft_printf("%s\n", argv[1]);
	set->n_philos = ft_atoi(argv[1]);
	ft_printf("n_philos %d\n", set->n_philos);
	set->time_to_die = ft_atoi(argv[2]);
	ft_printf("time_to_die %d\n", set->time_to_die);
	set->time_to_eat = ft_atoi(argv[3]);
	ft_printf("time_to_eat %d\n", set->time_to_eat);
	set->time_to_sleep = ft_atoi(argv[4]);
	ft_printf("time_to_sleep %d\n", set->time_to_sleep);
	if (argc == 6)
	{
		set->n_meals = ft_atoi(argv[5]);
		ft_printf("n_meals %d\n", set->n_meals);		
	}
	else
		set->n_meals = -1;
	return (0);
}
