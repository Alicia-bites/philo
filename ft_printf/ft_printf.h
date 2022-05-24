/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 10:50:07 by amarchan          #+#    #+#             */
/*   Updated: 2021/12/13 12:00:27 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <bsd/string.h>
# include <stdarg.h> 
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>

int		ft_printf(const char *type, ...);
int		ft_print_args(char c, va_list args);
int		ft_putchar_n(char c);
void	ft_putchar(char c);
int		ft_putstr_n(char *str);
int		ft_px(long unsigned int nbr, char *base);
int		ft_print_u(unsigned int nb);
int		ft_print_d(int nb);
int		ft_strlen(char *str);

#endif
