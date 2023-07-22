/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 19:30:46 by ykerdel           #+#    #+#             */
/*   Updated: 2023/07/22 17:33:59 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
    res = malloc(src_len - len + ft_strlen(swap) + 1);
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

char    *quote_str_get(char *str, size_t tk_count)
{
    size_t  i;
    size_t  j;
    char    *res;

    res = malloc(sizeof(char) * (ft_strlen(str) - tk_count + 1));
    if (!res)
        return (NULL);
    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == TK_D_QUOTE || str[i] == TK_S_QUOTE)
            i++;
        else
        {
            res[j] = str[i];
            j++;
            i++;
        }
    }
    res[j] = '\0';
    return (res);
}

int ms_open(char **str, char token)
{
    int fd;
    size_t i;

    i = 0;
    fd = 0;
    while ((*str)[i] && (*str)[i] != TK_PIPE)
    {
        if ((*str)[i] == token)
        {
            if ((*str)[i + 1] && (*str)[i + 1] == token) 
                fd = token_append(str, i, fd);
            else
                fd = token_redirect(str, i, fd, token);
        }
        i++;
    }
    return (fd);
}

size_t    ms_count_char(char *input, char c)
{
    size_t    nbr;
    size_t    i;

	nbr = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == c)
			nbr++;
		i++;
	}
    return (nbr);
}
