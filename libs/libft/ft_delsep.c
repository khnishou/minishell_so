/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delsep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 03:57:01 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/20 21:25:16 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

static size_t	ft_char_count(char *str)
{
	size_t	len;
	size_t	start;
	size_t	end;

	len = ft_strlen(str);
	start = 0;
	end = len;
	while (ft_isspace((unsigned char)str[start]))
		start++;
	while (end > start && ft_isspace((unsigned char)str[end - 1]))
		end--;
	return (end - start);
}

static char	*compact_space(int j, int is_sep, char *str, t_data *d)
{
	int		i;
	size_t	len;
	char	*result;

	i = -1;
	len = ft_char_count(str);
	result = (char *)ft_malloc(&(d->mem_list), sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	while (++i < (int)ft_strlen(str))
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		{
			if (!is_sep)
				result[j++] = ' ';
			is_sep = 1;
		}
		else
		{
			result[j++] = str[i];
			is_sep = 0;
		}
	}
	result[j] = '\0';
	return (result);
}

char	*ft_delsep(char *str, t_data *d)
{
	if (!str)
		return (NULL);
	return (ft_strtrim(compact_space(0, 0, str, d), " ", d));
}
