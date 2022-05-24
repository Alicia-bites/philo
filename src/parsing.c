/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:05:04 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/23 19:09:34 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_panic(int errcode)
{
	ft_putstr_fd("Error", 1, 2);
	if (errcode == WRONG_NARG)
		ft_printf("Usage :./philo number_of_philosophers time_to_die" \
		"time_to_eat" \
		"time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	else if (errcode == INVALID_ARG)
	exit(errcode);
}

int	init_philos(t_philo **philos, t_game *state)
{
	int	i;

	i = 0;
	*philos = malloc(sizeof(**philos) * state->pi.n_philos);
	if (!*philos)
		return (1);
	while (i < state->set.n_philos)
	{
		init_philo(&(*philos)[i], i + 1, state);
		i++;
	}
	return (0);
}

static void	init_philo(t_philo *philo, int id, t_game *state)
{
	philo->id = id;
	philo->last_eat = -1;
	philo->n_meals = 0;
	philo->state = state;
}

//check if argument is integer
static int	isinteger(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '-' || s[i] == '+')
			i++;
		if (!ft_isdigit(s[i]))
		{	
			ft_panic(NOT_INT);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (1);
}

//get rid of extra spaces before argument
static void	ft_strip(char *s)
{
	ft_lstrip(s);
	ft_rstrip(s);
}

//check if argument isn't smaller than INT_MIN or bigger than INT_MAX
static int	ft_invalid_int(long long arg)
{
	return (!(arg <= INT_MAX && arg >= INT_MIN));
}

//check if arguments are correct and if so returns 1
char **check_args(int argc, char **argv)
{
	long long	num;
	int			i;
	
	i = 1;
	while (i++ <= argc)
	{
		ft_strip(argv[i]);
		if (ft_strlen(argv[i]) == 0)
			ft_panic(EMPTY_STR);
		else if (ft_strlen(argv[i]) <= 11 && isinteger(argv[i]))
		{
			if (ft_invalid_int(ft_atoll(argv[i])))
				ft_panic(OUT_INT);
		}
	}
	return (argv);
}

int	ft_parse(t_settings *set, int argc, char **argv)
{
	argv = check_args(argc, argv);
	ft_printf("%s\n", argv[1]);
	set->n_philos = ft_atoi(argv[1]);
	set->time_to_die = ft_atoi(argv[2]);
	set->time_to_eat = ft_atoi(argv[3]);
	set->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		set->n_meals = ft_atoi(argv[5]);
	else
		set->n_meals = -1;
	return (0);
}
