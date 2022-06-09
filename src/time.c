/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:00:53 by amarchan          #+#    #+#             */
/*   Updated: 2022/06/09 10:45:59 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

void	get_starting_time(t_philo *philo)
{
	struct timeval	start;

	(void)*philo;
	gettimeofday(&start, 0);
	wait_until(philo, 0, &start);
}

//evaluate elapsed time since program started
unsigned long	elapsed_time_since_start(t_philo *philos)
{
	struct timeval	now;
	unsigned long	new_time;

	gettimeofday(&now, 0);
	new_time = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	new_time = new_time - philos->starting_time;
	return (new_time);
}

//make philo wait until moment_ms
void	wait_until(t_philo *philo, unsigned long moment_ms,
	struct timeval *time_ref)
{
	static struct timeval	static_time_ref;
	struct timeval			moment;
	struct timeval			now;
	unsigned long			now_long;
	unsigned long			static_time_ref_long;

	(void)*philo;
	moment = ft_convert(moment_ms);
	if (time_ref)
		static_time_ref = *time_ref;
	gettimeofday(&now, 0);
	static_time_ref_long = static_time_ref.tv_sec
		* 1000 + static_time_ref.tv_usec / 1000;
	while (!greater_than(time_sub(now, moment), static_time_ref_long))
	{
		now_long = now.tv_sec * 1000 + now.tv_usec / 1000;
		philo->timestamp = now_long - static_time_ref_long;
		if (philo_starved(philo))
			return ;
		usleep(10);
		gettimeofday(&now, 0);
	}
}
