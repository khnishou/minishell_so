/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 22:06:23 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/04 22:15:40 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*v;
	double	total;

	total = (double)count * (double)size;
	if (total > SIZE_MAX)
		return (NULL);
	v = ft_malloc(&(g_data.mem_list), (size_t)total);
	if (!v)
		return (NULL);
	ft_bzero(v, (size_t)total);
	return (v);
}
