/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isinteger.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 13:44:01 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/26 13:46:46 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

//check if argument is integer
int	isinteger(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '-' || s[i] == '+')
			i++;
		if (!ft_isdigit(s[i]))
			ft_panic(NOT_INT);
		i++;
	}
	return (1);
}