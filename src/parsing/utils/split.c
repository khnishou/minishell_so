/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:01:21 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/20 21:39:51 by ykerdel          ###   ########.fr       */
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

	ints[0] = 0;
	while ((*str)[ints[0]] && (*str)[ints[0]] != TK_PIPE)
		ints[0]++;
	tmp = ft_substr((*str), 0, ints[0], g_data);
	str1 = parse_str(tmp);
	cmd = ft_split(str1, '\t', g_data);
	if ((*str)[ints[0]] == TK_PIPE)
		ints[0]++;
	ints[1] = ints[0];
	ints[0] = 0;
	*str = ms_swapstr(*str, NULL, ints, g_data);
	return (cmd);
}
