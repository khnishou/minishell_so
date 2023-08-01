/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delsep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 03:57:01 by ykerdel           #+#    #+#             */
/*   Updated: 2023/07/30 17:05:46 by ykerdel          ###   ########.fr       */
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

char *compact_space(int i, int j, int is_previous_separator, char *str)
{
    size_t len = ft_char_count(str);
    char *result = (char *)malloc(sizeof(char) * (len + 1));
    if (result == NULL)
        return NULL;

    while (i < (int)ft_strlen(str))
    {
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        {
            if (!is_previous_separator)
                result[j++] = ' ';
            is_previous_separator = 1;
        }
        else
        {
            result[j++] = str[i];
            is_previous_separator = 0;
        }
        i++;
    }
    result[j] = '\0';
    return result;
}

char *ft_delsep(char *str)
{
    int j = 0;
    int i = 0;
    int is_previous_separator = 0;
    if (!str)
        return NULL;
    return (ft_strtrim(compact_space(i, j, is_previous_separator, str), " "));
}
