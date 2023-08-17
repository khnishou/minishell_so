/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 18:10:31 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/16 23:50:38 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int  ft_wordcount(char const *s, char c)
{
    int count;
    int i;
    count = 0;
    i = 0;
    while (s[i])
    {
        if (s[i] != c)
        {
            count++;
            while (s[i] != c && s[i])
                i++;
        }
        else
            i++;
    }
    return (count);
}
static int  ft_split_len(const char *s, int l, char c)
{
    int i;
    i = 0;
    while (s[l + i] != c && s[l + i])
        i++;
    return (i);
}
static int  ft_split_start(const char *s, char c, int l)
{
    while (s[l] == c)
        l++;
    return (l);
}
void    free_split(char **words)
{
    int i;
    i = 0;
    while (words[i] != NULL)
    {
        free(words[i]);
        i++;
    }
    free(words);
}
char    **ft_split(char const *s, char c, t_data *g_data)
{
    char    **t;
    int     j;
    int     l;
    j = 0;
    l = 0;
    t = (char **)ft_malloc(&g_data->mem_list, (ft_wordcount(s, c) + 1) * sizeof(char *));
    if (!t)
        return (NULL);
    while (s[l])
    {
        l = ft_split_start(s, c, l);
        if (ft_split_len(s, l, c) != 0)
        {
            t[j] = (char *)ft_malloc(&g_data->mem_list, (ft_split_len(s, l, c) + 1) * sizeof(char));
            if (!t[j])
                return (free_split(t), NULL);
            ft_strlcpy(t[j], s + l, ft_split_len(s, l, c) + 1);
            j++;
        }
        l += ft_split_len(s, l, c);
    }
    t[j] = NULL;
    return (t);
}