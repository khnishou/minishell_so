/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 13:45:49 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/04 22:26:16 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static size_t	ft_intlen(int n)
{
	size_t	i;

	i = 0;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*d;

	if (n == 0)
		return (ft_strdup("0"));
	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	len = ft_intlen(n);
	d = ft_malloc(&(g_data.mem_list), len + (n < 0) + 1);
	if (!d)
		return (NULL);
	d[len + (n < 0)] = 0;
	if (n < 0)
	{
		d[0] = '-';
		n = n * -1;
	}
	else
		len--;
	while (n != 0)
	{
		d[len--] = '0' + (n % 10);
		n = n / 10;
	}
	return (d);
}
