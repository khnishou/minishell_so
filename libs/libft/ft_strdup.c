/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:49:43 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/16 23:42:12 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strdup(const char *s, t_data *g_data)
{
	char	*d;
	size_t	len;

	len = ft_strlen(s) + 1;
	d = ft_malloc(&(g_data->mem_list), len);
	if (d == NULL)
		return (NULL);
	d = ft_memcpy (d, s, len);
	return (d);
}
