/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expention.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:33:25 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/15 01:56:58 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int    expend_heredoc(char *str, int i)
{
    i += 2;
    while (str[i] && str[i] == TK_SPACE)
        i++;
    if (str[i] == TK_PIPE)
        return (-1);
    while (str[i] && str[i] != TK_SPACE && str[i] != TK_PIPE)
    {
        if (str[i] == TK_D_QUOTE || str[i] == TK_S_QUOTE)
            i = ms_quote_skip(str, i, str[i]);
        if (i == -1)
            return (i);
        i++;
    }
    return (i);
}

int    expend_dollar(char **str, int i, bool flag)
{
    int    len;
    int    env_len;
    char      *env;

    len = 1;
    if (!(*str)[i + len] || (*str)[i + len] == TK_SPACE)
        return (i + 1);
    if (ft_isalpha((*str)[i + len]) || (*str)[i + len] == TK_UNDERSCORE)
        len++;
    while (ft_isalnum((*str)[i + len]) || (*str)[i + len] == TK_UNDERSCORE)
        len++;
    if ((*str)[i + 1] == TK_QUESTION_MARK)
    {
        env = ft_itoa(g_data.exit_status);
        len++;
    }
    else
        env = ms_getenv(ft_substr((*str), i + 1, len - 1));
    if (!env)
        env = NULL;
    if (flag)
        env = ft_delsep(env);
    (*str) = ms_swapstr((*str), env, i, len);
    env_len = ft_strlen(env);
    return (i + env_len - 1);
}

int expend_quote(char **str, int i, char token)
{
    i++;
    while (((*str)[i] && (*str)[i] != token))
    {
        if (token == TK_D_QUOTE && (*str)[i] == TK_DOLLAR)
            i = expend_dollar(str, i, false);
        i++;
    }
    if (!(*str)[i])
    {
        ft_printf("syntax error\n");
        return (-1);
    }
    i++;
    return (i);
}

char	*ms_expention(char *input)
{
	int	i;

	i = 0;
    if (input)
        while (input[i])
        {
            if (input[i] == TK_LESS && input[i + 1] && input[i + 1] == TK_LESS)
                i = expend_heredoc(input, i);
            else if (input[i] == TK_S_QUOTE || input[i] == TK_D_QUOTE)
                i = expend_quote(&input, i, input[i]);
            else if (input[i] == TK_DOLLAR)
                i = expend_dollar(&input, i, true);
            else
                i++;
            if (i == -1)
                return (NULL);
        }
	return (input);
}
