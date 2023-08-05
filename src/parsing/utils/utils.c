/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 19:30:46 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/04 22:18:29 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

size_t    ms_count_char(char *input, char c)
{
    size_t    nbr;
    size_t    i;

	nbr = 0;
	i = 0;
	if (input)
        while (input[i])
        {
            if (input[i] == c)
                nbr++;
            i++;
        }
    return (nbr);
}

char	*ms_swapstr(char *src, char *swap, size_t start, size_t len)
{
    int i;
    char *res;
    int end;
    size_t    src_len;

    src_len = ft_strlen(src);
    if (!src || start >= src_len)
        return (NULL);
    end = start + len;
    res = ft_malloc(&(g_data.mem_list), src_len - len + ft_strlen(swap) + 1);
    if (!res)
        return (NULL);
    i = -1;
    while (++i < (int) start)
        res[i] = src[i];
    start = 0;
    if (swap)
        while (swap[start])
            res[i++] = swap[start++];
    while (src[end])
        res[i++] = src[end++];
    res[i] = '\0';
    return (res);
}

int  ms_quote_skip(char *str, size_t i, char token)
{
    i++;
    while (str[i] && str[i] != token)
        i++;
    if (!str[i])
        return (-1);
    return (i);
}

char    *quote_str_get(char *str, size_t tk_count)
{
    size_t  i;
    size_t  j;
    char    token;
    char    *res;

    res = ft_malloc(&(g_data.mem_list), sizeof(char) * (ft_strlen(str) - tk_count + 1));
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

char    *ms_getenv(char *str)
{
    size_t  len;
    char    **env;

    env = g_data.envp;
    len = ft_strlen(str);
    while (*env)
    {
        if (!ft_strncmp(str, *env, len))
            return (*env + len + 1);
        env++;
    }
    return (NULL);
}
