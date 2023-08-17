
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

char *heredoc_expention(char *str, t_data *g_data)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == TK_DOLLAR)
            i = expend_dollar(&str, i, false, g_data);
        else
            i++;
    }
    return (str);
}

static int open_heredoc(char *str, char *exit, int tk_count, t_data *g_data)
{
    int     fd;
    char    *join;
    char    *line;

    line = NULL;
    join = NULL;
    ft_printf(GREEN);
    while (ft_strncmp(line, ft_strjoin(exit, "\n", g_data), ft_strlen(exit) + 1))
    {
        if (!tk_count && line)
            line = heredoc_expention(line, g_data);
        join = ft_strjoin(join, line, g_data);
        ft_printf("heredoc>  ");
        line = get_next_line(1);
    }
    fd = open("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0000777);
    if (fd == -1) {
        perror("Error opening heredoc file");
        return (-1);
    }
    write(fd, join, ft_strlen(join));
    ft_printf(RESET);
    return (fd);
}

int heredoc_handler(char **str, int index, t_data *g_data)
{
	int  ints[2];
    int  tk_count;
    char    *exit;
    
    ints[_j] = index + 2;
    while ((*str)[ints[_j]] && (*str)[ints[_j]] == TK_SPACE)
        ints[_j]++;
    ints[_start] = ints[_j];
    tk_count = 0;
    --ints[_j];
    while ((*str)[++ints[_j]] && (*str)[ints[_j]] != TK_SPACE && (*str)[ints[_j]] != TK_PIPE)
        if ((*str)[ints[_j]] == TK_D_QUOTE || (*str)[ints[_j]] == TK_S_QUOTE)
        {
            ints[_j] = ms_quote_skip((*str) , ints[_j], (*str)[ints[_j]]);
            tk_count += 2;
        }
    exit = quote_str_get(ft_substr((*str), ints[_start], ints[_j] - ints[_start], g_data), tk_count, g_data);
    ints[_start] = index;
    ints[_j] = ints[_j] - index;
    *str = ms_swapstr(*str, NULL, (size_t *)ints, g_data);
    ints[_j] = open_heredoc((*str), exit, tk_count, g_data);
    close(ints[_j]);
    ints[_j] = open("heredoc", O_RDWR | O_TRUNC | O_CREAT, 0000644);
    return (ints[_j]);
}
