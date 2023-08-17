/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delsep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 03:57:01 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/17 00:00:52 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int ft_isspace(char c)
{
    if (c == '\t' || c == '\n' || c == '\v' ||
        c == '\f' || c == '\r' || c == ' ')
        return 1;
    return 0;
}

static size_t ft_char_count(char *str)
{
    size_t len = ft_strlen(str);
    size_t start = 0;
    size_t end = len;

    while (ft_isspace((unsigned char)str[start]))
        start++;
    while (end > start && ft_isspace((unsigned char)str[end - 1]))
        end--;

    return (end - start);
}

char *compact_space(int ints[3], char *str, t_data *g_data)
{
    size_t len = ft_char_count(str);
    char *result = (char *)ft_malloc(&(g_data->mem_list), sizeof(char) * (len + 1));
    if (result == NULL)
        return NULL;

    while (ints[_i] < (int)ft_strlen(str))
    {
        if (str[ints[_i]] == ' ' || str[ints[_i]] == '\t' || str[ints[_i]] == '\n')
        {
            if (!ints[_is_previous_separator])
                result[ints[_j]++] = ' ';
            ints[_is_previous_separator] = 1;
        }
        else
        {
            result[ints[_j]++] = str[_i];
            ints[_is_previous_separator] = 0;
        }
        ints[_i]++;
    }
    result[ints[_j]] = '\0';
    return result;
}

char *ft_delsep(char *str, t_data *g_data)
{
    int ints[3];
    
    ints[0] = 0;
    ints[1] = 0;
    ints[2] = 0;
    if (!str)
        return NULL;
    return (ft_strtrim(compact_space(ints, str, g_data), " ", g_data));
}
