/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:00:04 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/08 12:12:20 by amarchan         ###   ########.fr       */
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

//errcodes
# define WRONG_NARG -1
# define WRONG_ARG -2
# define EMPTY_STR -3
# define OUT_INT -4
# define NOT_INT -5
# define MALLOC_FAILURE -6
# define THREAD_ERROR -7
# define INT_NEG -8
# define MUTEX_FAILURE -9
# define NO_PHILO -10

//a philosopher's day
// # define EAT "is eating"
// # define TAKE_FORK "has taken a fork"
// # define SLEEP "is sleeping"
// # define THINK "is thinking"
// # define  DIE "died"

# define EAT -42
# define TAKE_FORK -52
# define SLEEP -62
# define THINK -72
# define  DIE -82

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
	int				game_over;
	pthread_mutex_t	game_over_lock;
	t_settings		set;
}	t_game;

typedef struct t_fork
{
	int				fork_id;
	pthread_mutex_t	fork_is_taken;
}	t_fork;

typedef struct s_philo
{
	int					id;
	int					pid;
	unsigned long		last_eat;
	int					n_meals;
	unsigned long		starting_time;
	t_fork				*right_fork;
	t_fork				*left_fork;
	unsigned long		timestamp;
	pthread_t			thread;
	pthread_mutex_t		printf_mutex;
	t_game				*diner;
}	t_philo;

// main
int				init_game(t_philo *philos, t_game *diner);
void			init_philo(t_philo *philo, int id, t_game *diner);

//parsing
char			**check_args(int argc, char **argv, int *err);
int				ft_parse(int argc, char **argv, t_game *diner);
int				ft_panic(int errcode);

//start_diner
int				start_diner(t_philo *philos, t_game *diner);
void			*game(void *param);
unsigned long	get_time(t_philo *philos);
int				game_is_over(t_philo *philos);

//time
unsigned long	elapsed_time_since_start(t_philo *philos);
void			get_starting_time(t_philo *philo);
void			wait_until(unsigned long moment_ms, struct timeval *time_ref);

//time_utils
unsigned long	time_sub(struct timeval a, struct timeval b);
int				greater_than(unsigned long a, unsigned long b);
struct timeval	ft_convert(unsigned long moment_ms);

//wait
void			wait_and_add_waited_time(t_philo *philos, double *time_waited);
void			wait_if_even_nb_of_philo(t_philo *philos);
void			organize_queue_to_eat(t_philo *philos);

//create fork
int				deal_forks(t_philo *philos, t_settings *set);
int				give_fork_to_philos(t_philo *left_philo, t_philo *right_philo);
t_fork			*new_fork(int *has_failed);

//philo_does
int				ft_do(t_philo *philos, unsigned long time_to, int whattodo);
int				philo_thinks(t_philo *philos);
int				philo_sleeps(t_philo *philos);
int				philo_eats(t_philo *philos);
void			color_print(t_philo *philo, int whattodo);

//fork
int				tries(t_philo *philos, t_fork *fork);
int				grab_fork(t_philo *philos, t_fork *fork);
int				grab_forks(t_philo *philos);
int				drop_fork(t_fork *fork);
int				drop_forks(t_philo *philos);

//utils
int				ft_atoi(const char *str);
long long		ft_atoll(const char *str);
int				ft_isspace(int c);
int				ft_isdigit(int c);
int				ft_strlen(char *s);
void			ft_rstrip(char *s);
void			ft_lstrip(char *s);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memcpy(void *s1, const void *s2, size_t n);
void			ft_strip(char *s);
int				isinteger(char *s);
void			ft_bzero(void *s, unsigned int n);

//end_game
int				init_end_game(t_game *diner);
int				philo_starved(t_philo *philos);
int				game_is_over(t_philo *philos);

//clean
int				ft_clean(t_philo *philos, t_game *diner, int err);
int				ft_clean_with_forks(t_philo *philos, t_game *diner, int err);
void			free_forks(t_philo *philos);

#endif 