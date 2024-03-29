/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:01:21 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/03 05:22:38 by ykerdel          ###   ########.fr       */
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

char	**ms_split(char **str)
{
	size_t	i;
	char	**cmd;
	char	*str1;
	char	*tmp;

	i = 0;
	while ((*str)[i] && (*str)[i] != TK_PIPE)
		i++;
	tmp = ft_substr((*str), 0, i);
	str1 = parse_str(tmp);
	cmd = ft_split(str1, '\t');
	if ((*str)[i] == TK_PIPE)
		i++;
    *str = ms_swapstr(*str, NULL, 0, i);
	return (cmd);
}
