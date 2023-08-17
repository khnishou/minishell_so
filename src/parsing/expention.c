/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expention.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:33:25 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/17 01:49:41 by ykerdel          ###   ########.fr       */
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

int    expend_dollar(char **str, int i, bool flag, t_data *g_data)
{
    size_t    ints[2];
    char      *env;

    ints[_size] = 1;
    if (!(*str)[i + ints[_size]] || (*str)[i + ints[_size]] == TK_SPACE)
        return (i + 1);
    if (ft_isalpha((*str)[i + ints[_size]]) || (*str)[i + ints[_size]] == TK_UNDERSCORE)
        ints[_size]++;
    while (ft_isalnum((*str)[i + ints[_size]]) || (*str)[i + ints[_size]] == TK_UNDERSCORE)
        ints[_size]++;
    if ((*str)[i + 1] == TK_QUESTION_MARK && ints[_size]++)
        env = ft_itoa(exit_status, g_data);
    else
        env = ms_getenv(ft_substr((*str), i + 1, ints[_size] - 1, g_data), g_data);
    if (!env)
        env = NULL;
    if (flag)
        env = ft_delsep(env, g_data);
    ints[_env_len] = ints[_size];
    ints[_size] = i;
    (*str) = ms_swapstr((*str), env, ints, g_data);
    ints[_env_len] = ft_strlen(env);
    return (i + ints[_env_len] - 1);
}

int expend_quote(char **str, int i, char token, t_data *g_data)
{
    i++;
    while (((*str)[i] && (*str)[i] != token))
    {
        if (token == TK_D_QUOTE && (*str)[i] == TK_DOLLAR)
            i = expend_dollar(str, i, false, g_data);
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

char	*ms_expention(char *input, t_data *g_data)
{
	int	i;

	i = 0;
    if (input)
        while (input[i])
        {
            if (input[i] == TK_LESS && input[i + 1] && input[i + 1] == TK_LESS)
                i = expend_heredoc(input, i);
            else if (input[i] == TK_S_QUOTE || input[i] == TK_D_QUOTE)
                i = expend_quote(&input, i, input[i], g_data);
            else if (input[i] == TK_DOLLAR)
                i = expend_dollar(&input, i, true, g_data);
            else
                i++;
            if (i == -1)
                return (NULL);
        }
	return (input);
}
