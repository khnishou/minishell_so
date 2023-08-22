/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:42:25 by schibane          #+#    #+#             */
/*   Updated: 2023/08/20 22:15:00 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "./libft.h"
# include<stdarg.h>

int		ft_printf(const char *str, ...);
void	ft_putchar_count(char c, int *ret);
void	ft_putstr_count(char *str, int *ret);
void	ft_puthex_adress_count(unsigned long long nbr, int cap,
			int adr, int *ret);
void	ft_putnbr_count(int n, int *ret);
#endif