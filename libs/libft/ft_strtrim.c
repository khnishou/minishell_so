/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:45:42 by ykerdel           #+#    #+#             */
/*   Updated: 2023/07/25 01:42:00 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <stdio.h>

static int	in_set(char const c, char const *set)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(set);
	while (i < len)
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s, char const *set)
{
	int	start;
	int	end;

	start = 0;
	if (!s)
		return (NULL);
	while (in_set(s[start], set))
		start++;
	end = ft_strlen(s) - 1;
	if (!(start == (int) ft_strlen(s)))
		while (in_set(s[end], set))
			end--;
	return (ft_substr(s, start, end - start + 1));
}
