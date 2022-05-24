/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:00:04 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/24 13:16:00 by amarchan         ###   ########.fr       */
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
# define NOT_INT -5

typedef struct s_settings
{
	int	n_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	n_meals;
}	t_settings;

typedef struct s_game
{
	t_settings		set;
}	t_game;

typedef struct s_philo
{
	int					id;
	int					pid;
	unsigned long		last_eat;
	int					n_meals;
	t_game				*state;
}	t_philo;

//parsing
int			ft_parse(int argc, char **argv);
void		ft_panic(int errcode);
int			init_game();

//utils
int			ft_atoi(const char *str);
long long	ft_atoll(const char *str);
int			ft_isspace(int c);
int			ft_isdigit(int c);
int			ft_strlen(char *s);
void		ft_rstrip(char *s);
void		ft_lstrip(char *s);


//main
#endif 