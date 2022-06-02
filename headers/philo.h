/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:00:04 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/02 19:18:16 by amarchan         ###   ########.fr       */
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
# define MUTEX_FAIL -9

//a philosopher's day
# define EAT "is eating"
# define TAKE_FORK "has taken a fork"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define  DIE "died"

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

typedef struct	t_fork
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
	pthread_mutex_t		*print;
	t_game				*state;
}	t_philo;

// main
int				init_game(t_philo *philos, t_game *state);
void 			init_philo(t_philo *philo, int id, t_game *state);

//parsing
char 			**check_args(int argc, char **argv, int *err);
int				ft_parse(int argc, char **argv, t_game *state);
int				ft_panic(int errcode);

//lock_printf
int				init_printf_lock(t_philo *philos);

//start_simulation
int				start_simulation(t_philo *philos, t_game *state);
void			*sim(void *param);
unsigned long	get_time(t_philo *philos);
int				game_is_over(t_philo *philos);

//time
unsigned long	elapsed_time_since_start(t_philo *philos);
void			get_starting_time(t_philo *philos);
void			ft_wait_until(unsigned long moment_ms, struct timeval *time_ref);

//time_utils
unsigned long	time_diff(struct timeval a, struct timeval b);
int				is_greater_than(unsigned long a, unsigned long b);
struct timeval	ft_convert(unsigned long moment_ms);

//wait
void			wait_if_even_nb_of_philo(t_philo *philos);
void			wait_to_eat(t_philo *philos);
unsigned long	when_is_next_meal(t_philo *philos);

//create fork
int				init_forks(t_philo *philos, t_settings set);
int				give_fork_to_philos(t_philo *left_philo, t_philo *right_philo);
t_fork			*create_fork(void);

//philo_does
int				ft_do(t_philo *philos, unsigned long time_to, char *whattodo);
int				philo_thinks(t_philo *philos);
int				philo_sleeps(t_philo *philos);
int				philo_eats(t_philo *philos);

//fork
void			add_waited_time(t_philo *philos, unsigned long *time_waited);
int				tries(t_philo *philos, t_fork *fork);
int 			grab_fork(t_philo *philos, t_fork *fork);
int				grab_forks(t_philo *philos);
int				drop_fork(t_fork *fork);
int				drop_forks(t_philo *philos);

//is_fork_free
int				philo_grabs_fork(t_philo *philos);
int				wait(t_philo *philos);

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
int				init_end_game(t_game *state);
int 			kill_philo_if_he_starved(t_philo *philos);
int				game_is_over(t_philo *philos);

//main
#endif 