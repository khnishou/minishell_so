/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 19:30:46 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/29 17:28:11 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ms_count_char(char *input, char c)
{
	int	nbr;
	int	i;

	nbr = 0;
	i = 0;
	if (input)
	{
		while (input[i])
		{
			if (input[i] == c)
				nbr++;
			i++;
		}
	}
	return (nbr);
}

char	*ms_swapstr(char *src, char *swap, int *ints, t_data *g_data)
{
	int		i;
	char	*res;
	int		end;
	int		src_len;

	src_len = ft_strlen(src);
	if (!src || ints[0] >= src_len)
		return (NULL);
	end = ints[0] + ints[1];
	res = ft_malloc(&(g_data->mem_list),
			src_len - ints[1] + ft_strlen(swap) + 1);
	if (!res)
		return (NULL);
	i = -1;
	while (++i < (int) ints[0])
		res[i] = src[i];
	ints[0] = 0;
	if (swap)
		while (swap[ints[0]])
			res[i++] = swap[ints[0]++];
	while (src[end])
		res[i++] = src[end++];
	res[i] = '\0';
	return (res);
}

int	ms_quote_skip(char *str, int i, char token)
{
	i++;
	while (str[i] && str[i] != token)
		i++;
	if (!str[i])
		return (-1);
	return (i);
}

char	*get_q(char *str, int c, t_data *g_data)
{
	int		i;
	int		j;
	char	token;
	char	*res;

	res = ft_malloc(&g_data->mem_list, sizeof(char) * (ft_strlen(str) - c + 1));
	if (!res)
		return (NULL);
	token = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == TK_D_QUOTE || str[i] == TK_S_QUOTE) && !token)
			token = str[i++];
		if (str[i] == token)
		{
			i++;
			token = 0;
		}
		else
			res[j++] = str[i++];
	}
	res[j] = 0;
	return (res);
}

char	*ms_getenv(char *str, t_data *g_data)
{
	int		len;
	char	**env;

	str = ft_strjoin(str, "=", g_data);
	env = g_data->envp;
	len = ft_strlen(str) - 1;
	while (*env)
	{
		if (!ft_strncmp(str, *env, len))
			return (*env + len + 1);
		env++;
	}
	return (NULL);
}
