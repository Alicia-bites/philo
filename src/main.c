/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:35:27 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/24 13:04:46 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{	
	if (argc == 5 || argc == 6)
		ft_parse(argc, argv);
	else
		ft_panic(WRONG_NARG);
	init_game();
	return (0);
}