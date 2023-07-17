/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 20:01:21 by ykerdel           #+#    #+#             */
/*   Updated: 2023/07/17 16:51:11 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	quote_skip(char *str, size_t i)
{
	size_t	quote_count;

	quote_count = 0;
	while (str[i] && str[i] != TK_SPACE && !(quote_count % 2))
		{
			if (str[i] == TK_D_QUOTE || str[i] == TK_S_QUOTE)
				quote_count++;
			else
				i++;
		}
	return (i);
}

size_t	split_size(char *str)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	if (str[i] && str[i] == TK_PIPE)
		i++;
	while (str[i] && str[i] != TK_PIPE)
	{
		while (str[i] && str[i] == TK_SPACE)
			i++;
		i = quote_skip(str, i);
		size++;
		i++;
	}
	return (size);
}

char	**ms_split(char **str, size_t size)
{
	size_t	i;
	size_t	i_tab;
	size_t	start;
	char	**cmd;

	cmd = (char **)malloc(sizeof(char) * (size + 1));
	if (!cmd)
		return (NULL);
	i = 0;
	i_tab = 0;
	if ((*str)[i] && (*str)[i] == TK_PIPE)
		i++;
	while ((*str)[i] && (*str)[i] != TK_PIPE)
	{
		while ((*str)[i] && (*str)[i] == TK_SPACE)
			i++;
		start = i;
		i = quote_skip((*str), i);
		cmd[i_tab] = ft_substr((*str), start, i - start);
		printf("cmd[i]%s\n", cmd[i_tab]);
		//printf("cmd[%zu] = %s\n", i_tab, cmd[i_tab]);
		i_tab++;
		//i++;
	}
	cmd[i_tab] = NULL;
	// int	l = 0;
	// while (l < (int)size)
	// 	printf("%s\n", cmd[l++]);
		
	(*str) = ms_swapstr((*str), NULL, 0, i + 1);
	return (cmd);
}
