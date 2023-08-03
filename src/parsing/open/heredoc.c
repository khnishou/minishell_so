
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 23:30:46 by ykerdel           #+#    #+#             */
/*   Updated: 2023/07/25 16:07:04 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char *heredoc_expention(char *str, int *g_exit_status)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == TK_DOLLAR)
            i = expend_dollar(&str, i, g_exit_status, false);
        else
            i++;
    }
    return (str);
}

static int open_heredoc(char *str, char *exit, int tk_count, int *g_exit_status)
{
    int     fd;
    char    *join;
    char    *line;

    line = NULL;
    join = NULL;
    ft_printf(GREEN);
    while (ft_strncmp(line, ft_strjoin(exit, "\n"), ft_strlen(exit) + 1))
    {
        if (!tk_count && line)
            line = heredoc_expention(line, g_exit_status);
        join = ft_strjoin(join, line);
        ft_printf("heredoc>  ");
        line = get_next_line(1);
    }
    fd = open("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0000644);
    if (fd == -1) {
        perror("Error opening heredoc file");
        return (-1);
    }
    write(fd, join, ft_strlen(join));
    ft_printf(RESET);
    return (fd);
}

int heredoc_handler(char **str, int index, int *g_exit_status)
{
	int  start;
    int  i;
    int  tk_count;
    char    *exit;
    
    i = index + 2;
    while ((*str)[i] && (*str)[i] == TK_SPACE)
        i++;
    start = i;
    tk_count = 0;
    while ((*str)[i] && (*str)[i] != TK_SPACE && (*str)[i] != TK_PIPE)
    {
        if ((*str)[i] == TK_D_QUOTE || (*str)[i] == TK_S_QUOTE)
        {
            i = ms_quote_skip((*str) , i, (*str)[i]);
            tk_count += 2;
        }
        i++;
    }
    exit = quote_str_get(ft_substr((*str), start, i - start), tk_count);
    *str = ms_swapstr(*str, NULL, index, i - index);
    i = open_heredoc((*str), exit, tk_count, g_exit_status);
    return (i);
}
