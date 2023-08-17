/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:01:21 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/17 01:41:48 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*parse_str(char *str)
{
	size_t	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == TK_SPACE)
			str[i] = '\t';
	}
	i = -1;
	while (str[++i])
	{
		if (str[i] == TK_S_QUOTE || str[i] == TK_D_QUOTE)
		{
			i++;
			while (str[i] != TK_S_QUOTE && str[i] != TK_D_QUOTE)
			{
				if (str[i] == '\t')
					str[i] = TK_SPACE;
				i++;
			}
		}
	}
	return (str);
}

char	**ms_split(char **str, t_data *g_data)
{
	size_t	ints[2];
	char	**cmd;
	char	*str1;
	char	*tmp;

	ints[_i] = 0;
	while ((*str)[ints[_i]] && (*str)[ints[_i]] != TK_PIPE)
		ints[_i]++;
	tmp = ft_substr((*str), 0, ints[_i], g_data);
	str1 = parse_str(tmp);
	cmd = ft_split(str1, '\t', g_data);
	if ((*str)[ints[_i]] == TK_PIPE)
		ints[_i]++;
	ints[_j] = ints[_i];
	ints[_i] = 0;
    *str = ms_swapstr(*str, NULL, ints, g_data);
	return (cmd);
}
