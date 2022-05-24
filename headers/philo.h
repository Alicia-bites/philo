/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:00:04 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/23 19:04:56 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>

# define WRONG_NARG -1
# define WRONG_ARG -2
# define EMPTY_STR -3
# define OUT_INT -4

typedef struct s_settings
{
	int	n_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	n_meals;
}	t_settings;

typedef struct s_philo
{
	int					id;
	int					pid;
	unsigned long		last_eat;
	int					n_meals;
	t_game				*state;
}	t_philo;

typedef struct s_game
{
	t_settings		set;
}	t_game;

//parsing
int			ft_parse(t_philos_args *pi, int argc, char **argv);
void		ft_panic(int errcode);

//utils
int			ft_atoi(const char *str);
long long	ft_atoll(const char *str);
int			ft_isspace(int c);
int			ft_isdigit(int c);


//main
#endif 