/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:10:51 by ykerdel           #+#    #+#             */
/*   Updated: 2023/07/24 19:19:58 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char *ft_strjoin(char *s1, char *s2)
{
	size_t i;
	size_t j;
	char *join;

	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
		return (NULL);
	i = 0;
	j = 0;
	if (s1)
		while (s1[i])
			join[j++] = s1[i++];
	i = 0;
	if (s2)
		while (s2[i])
			join[j++] = s2[i++];
	join[j] = 0;
	return (join);
}
