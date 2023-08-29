/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expention.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:33:25 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/29 19:23:34 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	expend_heredoc(char *str, int i)
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

int	expend_dollar(char **str, int i, bool flag, t_data *g)
{
	int		fc[2];
	char	*env;

	fc[0] = 1;
	if (!(*str)[i + fc[0]] || (*str)[i + fc[0]] == TK_SPACE)
		return (i + 1);
	if (ft_isalpha((*str)[i + fc[0]]) || (*str)[i + fc[0]] == '_')
		fc[0]++;
	while (ft_isalnum((*str)[i + fc[0]]) || (*str)[i + fc[0]] == '_')
		fc[0]++;
	if ((*str)[i + 1] == TK_QUESTION_MARK && fc[0]++)
		env = ft_itoa(g_exit_status, g);
	else
		env = ms_getenv(ft_substr((*str), i + 1, fc[0] - 1, g), g);
	if (!env)
		env = NULL;
	if (flag)
		env = ft_delsep(env, g);
	fc[1] = fc[0];
	fc[0] = i;
	(*str) = ms_swapstr((*str), env, fc, g);
	fc[1] = ft_strlen(env);
	return (i + fc[1] - 1);
}

int	expend_quote(char **str, int i, char token, t_data *g_data)
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
		ft_printf(RED"minishell :syntax error\n"CYAN);
		g_exit_status = 1;
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
	{
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
	}
	return (input);
}
