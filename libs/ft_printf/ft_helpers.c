/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:42:19 by schibane          #+#    #+#             */
/*   Updated: 2023/07/24 20:49:01 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void	ft_putchar_count(char c, int *ret)
{
	ft_putchar_fd(c, 1);
	*ret = *ret + 1;
}

void	ft_putstr_count(char *str, int *ret)
{
	if (!str)
	{
		write(1, "(null)", 6);
		*ret = 6;
	}
	else
	{
		ft_putstr_fd(str, 1);
		*ret = ft_strlen(str);
	}
}

void	ft_puthex_adress_count(unsigned long long nbr, int cap,
	int adr, int *ret)
{
	if (adr)
	{
		write(1, "0x", 2);
		*ret = *ret + 2;
	}
	if (nbr / 16)
		ft_puthex_adress_count(nbr / 16, cap, 0, ret);
	if (cap)
		write(1, &"0123456789ABCDEF"[nbr % 16], 1);
	else
		write(1, &"0123456789abcdef"[nbr % 16], 1);
	*ret = *ret + 1;
}

static int	ft_calculnbrlen(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		i ++;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		i ++;
	}
	return (i);
}

void	ft_putnbr_count(int n, int *ret)
{
	ft_putnbr_fd(n, 1);
	*ret += ft_calculnbrlen(n);
}
