/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:54:56 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/17 01:18:55 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int single_redirect(char **str, int *ints, char token, t_data *g_data)
{
    int  start;
    int  i;

    i = ints[_i];
    i++;  
    if (ints[_fd] > 0)
        close(ints[_fd]);
    while ((*str)[i] && (*str)[i] == TK_SPACE)
        i++;
    if ((*str)[i] == TK_PIPE)
        return (-2);
    start = i;
    while ((*str)[i] && (ft_isalnum((*str)[i]) || (*str)[i] == TK_PERIOD || (*str)[i] == TK_HYPHEN || (*str)[i] == TK_UNDERSCORE))
        i++;
    if (token == TK_GREATER)
		ints[_fd] = open(ft_substr(*str, start, i - start, g_data), O_RDWR | O_TRUNC | O_CREAT, 0000644);
    else if (token == TK_LESS)
        ints[_fd] = open(ft_substr(*str, start, i - start, g_data), O_RDONLY);
    if (ints[_fd] == -1)
        perror("Minishell");
    ints[_j] = i - ints[_i];
    *str = ms_swapstr(*str, NULL, (size_t *)ints, g_data);
    return (ints[_fd]);
}

int append_handler(char **str, int index, t_data *g_data)
{
    size_t ints[2];
	// size_t  start;
    // size_t  i;
    int     fd;
    char    *file_name;
    
    ints[_j] = index;
    ints[_j] += 2;
    while ((*str)[ints[_j]] && (*str)[ints[_j]] == TK_SPACE)
        ints[_j]++;
    if ((*str)[ints[_j]] == TK_PIPE)
        return (-1);
    ints[_start] = ints[_j];
    while ((*str)[ints[_j]] && (ft_isalnum((*str)[ints[_j]]) || (*str)[ints[_j]] == TK_PERIOD || (*str)[ints[_j]] == TK_HYPHEN || (*str)[ints[_j]] == TK_UNDERSCORE))
        ints[_j]++;
    file_name = ft_substr(*str, ints[_start], ints[_j] - ints[_start], g_data);
    ms_clean(&file_name, g_data);
    fd = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0000644);
    if (fd == -1)
        perror("Minishell");
    ints[_start] = index;
    ints[_j] = ints[_j] - index;
    *str = ms_swapstr(*str, NULL, ints, g_data);
    return (fd);
}

int double_redirect(char **str, size_t index, char token, t_data *g_data)
{
    int i;
    int fd;
    
    i = index + 2;
    while ((*str)[i] && (*str)[i] == TK_SPACE)
        i++;
    if ((*str)[i] == TK_PIPE)
        return (-2);
    if (token == TK_GREATER)
        fd = append_handler(str, index, g_data);
    else if (token == TK_LESS)
        fd = heredoc_handler(str, index, g_data);
    return (fd);
}

int ms_open(char **str, char token, t_data *g_data)
{
    int ints[2];

    ints[_i] = 0;
    ints[_fd] = 0;
    while ((*str)[ints[_i]] && (*str)[ints[_i]] != TK_PIPE)
    {
        if ((*str)[ints[_i]] == token)
        {
            if ((*str)[ints[_i] + 1] && (*str)[ints[_i] + 1] == token)
            {
                if (ints[_fd] > 0)
                    close(ints[_fd]);
                ints[_fd] = double_redirect(str, ints[_i], token, g_data);
            }
            else
                ints[_fd] = single_redirect(str, ints, token, g_data);
        }
        ints[_i]++;
    }
    return (ints[_fd]);
}
