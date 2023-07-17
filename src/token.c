/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:54:56 by ykerdel           #+#    #+#             */
/*   Updated: 2023/07/17 15:31:23 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t    token_dollar(char **str, int i, int *exit_status)
{
    size_t    len;
    size_t    env_len;
    char      *env;

    len = 1;
    if (ft_isalpha((*str)[i + len]) || (*str)[i + len] == TK_UNDERSCORE)
        len++;
    while (ft_isalnum((*str)[i + len]) || (*str)[i + len] == TK_UNDERSCORE)
        len++;
    if ((*str)[i + 1] == TK_QUESTION_MARK)
    {
        env = ft_itoa(*exit_status);
        len++;
    }
    else
        env = getenv(ft_substr((*str), i + 1, len - 1));
    if (!env)
        env = NULL;
    (*str) = ms_swapstr((*str), env, i, len);
    env_len = ft_strlen(env);
    return (i + env_len - 1);
}

size_t token_quote(char **str, size_t i, char token, int *exit_status)
{
    int loop;

    loop = 1;
    i++;
    while (((*str)[i] && (*str)[i] != token) || loop)
    {
        loop = 0;
        if (token == TK_D_QUOTE && (*str)[i] == TK_DOLLAR)
            i = token_dollar(str, i, exit_status);
        i++;
    }
    i++;
    return (i);
}

int token_redirect(char **str, size_t index, int fd, char token)
{
    size_t  start;
    size_t  i;

    i = index;
    i++;  
    if (fd >= 0)
        close(fd);
    while ((*str)[i] && (*str)[i] == TK_SPACE)
        i++;
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

int token_append(char **str, size_t index, int fd)
{
	size_t  start;
    size_t  i;
    
    i = index;
    i += 2; 
    if (fd >= 0)
        close(fd);
    while ((*str)[i] && (*str)[i] == TK_SPACE)
        i++;
    start = i;
    while ((*str)[i] && (ft_isalnum((*str)[i]) || (*str)[i] == TK_PERIOD || (*str)[i] == TK_HYPHEN || (*str)[i] == TK_UNDERSCORE))
    i++;
    fd = open(ft_substr(*str, start, i - start), O_RDWR | O_CREAT, 0000644);
    if (fd == -1)
        perror("Minishell");
    *str = ms_swapstr(*str, NULL, index, i - index);
    return (fd);
}

size_t  token_heredoc(char **str, size_t index)
{
    size_t  start;
    size_t  i;
    size_t  tk_count;
    char    *exit;

    i = index;
    i += 2;
    while ((*str)[i] && (*str)[i] == TK_SPACE)
        i++;
    start = i;
    tk_count = 0;
    while ((*str)[i] && (*str)[i] != TK_SPACE)
    {
        if ((*str)[i] == TK_D_QUOTE || (*str)[i] == TK_S_QUOTE)
            tk_count++;
        i++;
    }
    exit = quote_str_get(ft_substr((*str), start, i - start), tk_count);
    printf("exit = %s\n", exit);
    *str = ms_swapstr(*str, NULL, index, i - index);
    printf(GREEN);
    while (ft_strncmp(readline("heredoc>  "), exit, ft_strlen(exit) + 1))
        ;
    printf(RESET);
    return (i);
}
