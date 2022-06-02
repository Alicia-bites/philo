/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:00:53 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/02 19:19:00 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	get_starting_time(t_philo *philos)
{
	struct timeval	start;
	unsigned long	starting_time;
	int	i;

	i = 0;
	gettimeofday(&start, 0);
	// printf("%ld\n", start.tv_sec);
	// printf("%ld\n", start.tv_usec);
	// printf("%ld\n", philos->starting_time = (start.tv_sec * 1000)
	// 	+ (start.tv_usec / 1000));
	starting_time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	while (i < philos->state->set.n_philos)
	{
		philos[i].starting_time = starting_time;
		// printf("%lu\n", philos[i].starting_time);
		i++;
	}
	// printf("starting time %lu\n", philos->starting_time);
}

//evaluate elapsed time since program started
unsigned long	elapsed_time_since_start(t_philo *philos)
{
	struct 			timeval	now;
	unsigned long	new_time;
	
	gettimeofday(&now, 0);
	new_time = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	new_time = new_time - philos->starting_time;
	// printf("nelw time : %ld | starting time %ld\n", new_time, philos->starting_time);
	return (new_time);
}

//make philo wait until moment_ms
void	ft_wait_until(unsigned long moment_ms, struct timeval *time_ref)
{
	static struct timeval	static_time_ref;
	struct	timeval			moment;
	struct timeval			now;
	unsigned long			static_time_ref_long;

	moment = ft_convert(moment_ms);
	if (time_ref)
		static_time_ref = *time_ref;
	gettimeofday(&now, 0);
	static_time_ref_long = static_time_ref.tv_sec
		* 1000 + static_time_ref.tv_usec / 1000;
	while (!is_greater_than(time_diff(now, moment), static_time_ref_long))
	{
		usleep(10);
		gettimeofday(&now, 0);
	}
}