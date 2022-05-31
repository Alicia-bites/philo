/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:00:04 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/31 15:48:02 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>
# include <pthread.h>
// # include "../printf/printf.h"

# define WRONG_NARG -1
# define WRONG_ARG -2
# define EMPTY_STR -3
# define OUT_INT -4
# define NOT_INT -5
# define MALLOC_FAILURE -6
# define THREAD_ERROR -7
# define INT_NEG -8
# define MUTEX_FAIL -9

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
	int				is_simulation_over;
	t_settings		set;
}	t_game;

typedef struct	t_fork
{
	int				fork_id;
	pthread_mutex_t	fork_is_taken;
}	t_fork;

typedef struct s_philo
{
	int					id;
	int					pid;
	int					last_eat;
	int					n_meals;
	unsigned long		starting_time;
	t_fork				right_fork;
	t_fork				left_fork;
	unsigned long		timestamp;
	pthread_t			thread;
	t_game				state;
}	t_philo;

// main
int	init_game(t_philo *philos, t_game state);
void init_philo(t_philo *philo, int id, t_game state);

//parsing
char 		**check_args(int argc, char **argv, int *err);
int			ft_parse(int argc, char **argv, t_game *state);
int		ft_panic(int errcode);

//start_simulation
void	start_simulation(t_philo *philos, t_game state);
void	*sim(void *param);
void	set_start_time(t_philo *philos);
int		sim_is_over(t_philo *philos);
void	philo_thinks(t_philo *philos);
void	philo_sleeps(t_philo *philos);
void	philo_eats(t_philo *philos);
int		can_eat(t_philo *philos);

//fork_handlers
int	init_forks(t_philo *philos, t_settings set);

//philo_does
void		philo_thinks(t_philo *philos);
void		philo_sleeps(t_philo *philos);
void		philo_eats(t_philo *philos);
int			can_eat(t_philo *philos);

//utils
int			ft_atoi(const char *str);
long long	ft_atoll(const char *str);
int			ft_isspace(int c);
int			ft_isdigit(int c);
int			ft_strlen(char *s);
void		ft_rstrip(char *s);
void		ft_lstrip(char *s);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memcpy(void *s1, const void *s2, size_t n);
void		ft_strip(char *s);
int			isinteger(char *s);
void		ft_bzero(void *s, unsigned int n);


//main
#endif 