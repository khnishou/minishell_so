/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:37:34 by schibane          #+#    #+#             */
/*   Updated: 2023/07/24 20:49:00 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static int	ft_calculunsignednbrlen(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		i ++;
	}
	return (i);
}

static	void	ft_putnbrunsigned_fd(unsigned int n, int fd)
{
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd((char)((n % 10) + '0'), fd);
	}
	else if (n < 10)
		ft_putchar_fd((char)(n + '0'), fd);
}

static	void	ft_putnbrunsigned_count(unsigned int n, int *ret)
{
	ft_putnbrunsigned_fd(n, 1);
	*ret += ft_calculunsignednbrlen(n);
}

static int	ft_dispatcher(char c, va_list ap)
{
	int	ret;

	ret = 0;
	if (c == '%')
		ft_putchar_count(c, &ret);
	else if (c == 'c')
		ft_putchar_count(va_arg(ap, int), &ret);
	else if (c == 's')
		ft_putstr_count(va_arg(ap, char *), &ret);
	else if (c == 'p')
		ft_puthex_adress_count(va_arg(ap, unsigned long long), 0, 1, &ret);
	else if (c == 'X')
		ft_puthex_adress_count(va_arg(ap, unsigned int), 1, 0, &ret);
	else if (c == 'x')
		ft_puthex_adress_count(va_arg(ap, unsigned int), 0, 0, &ret);
	else if (c == 'd' || c == 'i')
		ft_putnbr_count(va_arg(ap, int), &ret);
	else if (c == 'u')
		ft_putnbrunsigned_count(va_arg(ap, unsigned int), &ret);
	else
		return (-1);
	return (ret);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		count;
	int		x;

	count = 0;
	i = 0;
	x = 0;
	va_start(ap, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			x = ft_dispatcher(str[i + 1], ap);
			if (x == -1)
				return (0);
			count += x;
			i ++;
		}
		else
			ft_putchar_count(str[i], &count);
		i ++;
	}
	return (count);
}
