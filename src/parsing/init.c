/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:52:38 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/22 22:57:21 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_clean(char **str, t_data *g_data)
{
	int	tk_count;
	int	i;

	i = 0;
	tk_count = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == TK_D_QUOTE || (*str)[i] == TK_S_QUOTE)
		{
			i = ms_quote_skip((*str), i, (*str)[i]);
			tk_count += 2;
		}
		i++;
	}
	(*str) = get_q((*str), tk_count, g_data);
}

t_exe	*ms_init(char *input, t_data *g)
{
	t_exe	*exe;
	size_t	i;

	exe = (t_exe *) ft_malloc(&(g->mem_list), sizeof(t_exe) * (g->nb_pipe + 1));
	if (!exe)
		ms_exit(MALLOC_ERR);
	input = ms_expention(input, g);
	i = 0;
	while (i <= (size_t)g->nb_pipe)
	{
		exe[i].index = i;
		exe[i].fd_in = ms_open(&input, TK_LESS, g, i);
		exe[i].fd_out = ms_open(&input, TK_GREATER, g, i);
		ms_clean(&input, g);
		exe[i].cmd = ms_split(&input, g);
		if (i != (size_t)g->nb_pipe)
			pipe(exe[i].pipe);
		if (!check_cmd(exe[i].cmd[0]))
			exe[i].path = find_path(exe[i].cmd[0], g);
		else
			exe[i].path = NULL;
		i++;
	}
	return (exe);
}
