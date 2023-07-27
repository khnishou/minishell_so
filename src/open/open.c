/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:54:56 by ykerdel           #+#    #+#             */
/*   Updated: 2023/07/27 16:46:02 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int single_redirect(char **str, int index, int fd, char token)
{
    int  start;
    int  i;

    i = index;
    i++;  
    if (fd > 0)
        close(fd);
    while ((*str)[i] && (*str)[i] == TK_SPACE)
        i++;
    if ((*str)[i] == TK_PIPE)
        return (-2);
    start = i;
    while ((*str)[i] && (ft_isalnum((*str)[i]) || (*str)[i] == TK_PERIOD || (*str)[i] == TK_HYPHEN || (*str)[i] == TK_UNDERSCORE))
        i++;
    if (token == TK_GREATER)
		fd = open(ft_substr(*str, start, i - start), O_RDWR | O_TRUNC | O_CREAT, 0000644);
    else if (token == TK_LESS)
        fd = open(ft_substr(*str, start, i - start), O_RDONLY);
    if (fd == -1)
        perror("Minishell");
    *str = ms_swapstr(*str, NULL, index, i - index);
    return (fd);
}

int append_handler(char **str, int index)
{
	size_t  start;
    size_t  i;
    int fd;
    
    i = index;
    i += 2;
    while ((*str)[i] && (*str)[i] == TK_SPACE)
        i++;
    if ((*str)[i] == TK_PIPE)
        return (-1);
    start = i;
    while ((*str)[i] && (ft_isalnum((*str)[i]) || (*str)[i] == TK_PERIOD || (*str)[i] == TK_HYPHEN || (*str)[i] == TK_UNDERSCORE))
    i++;
    fd = open(ft_substr(*str, start, i - start), O_RDWR | O_CREAT, 0000644);
    if (fd == -1)
        perror("Minishell");
    *str = ms_swapstr(*str, NULL, index, i - index);
    return (fd);
}

int double_redirect(char **str, size_t index, char token, int *g_exit_status)
{
    int i;
    int fd;
    
    i = index + 2;
    while ((*str)[i] && (*str)[i] == TK_SPACE)
        i++;
    if ((*str)[i] == TK_PIPE)
        return (-2);
    if (token == TK_GREATER)
        fd = append_handler(str, index);
    else if (token == TK_LESS)
        fd = heredoc_handler(str, index, g_exit_status);
    return (fd);
}

int ms_open(char **str, char token, int *g_exit_status)
{
    int fd;
    int i;

    i = 0;
    fd = 0;
    while ((*str)[i] && (*str)[i] != TK_PIPE)
    {
        if ((*str)[i] == token)
        {
            if ((*str)[i + 1] && (*str)[i + 1] == token)
            {
                if (fd > 0)
                    close(fd);
                fd = double_redirect(str, i, token, g_exit_status);
            }
            else
                fd = single_redirect(str, i, fd, token);
        }
        i++;
    }
    return (fd);
}
