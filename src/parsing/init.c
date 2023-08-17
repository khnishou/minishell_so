/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:52:38 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/17 14:59:03 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ms_clean(char **str, t_data *g_data)
{
	int tk_count;
	int i;

	i = 0;
	tk_count = 0;
    while ((*str)[i])
    {
        if ((*str)[i] == TK_D_QUOTE || (*str)[i] == TK_S_QUOTE)
        {
            i = ms_quote_skip((*str) , i, (*str)[i]);
            tk_count += 2;
        }
        i++;
    }
	(*str) = quote_str_get((*str), tk_count, g_data);
}

t_exe *ms_init(char *input, t_data *g_data)
{
	t_exe	*exe;
	size_t	i;

	exe = (t_exe *) ft_malloc(&(g_data->mem_list), sizeof(t_exe) * (g_data->nb_pipe + 1));
	if (!exe)
		ms_exit(MALLOC_ERR);
	input = ms_expention(input, g_data);
	i = 0;
	while (i <= (size_t)g_data->nb_pipe)
	{
		exe[i].index = i;
		exe[i].fd_in = ms_open(&input, TK_LESS, g_data);
		exe[i].fd_out = ms_open(&input, TK_GREATER, g_data);
		ms_clean(&input, g_data);
		exe[i].cmd = ms_split(&input, g_data);
		if (i != (size_t)g_data->nb_pipe)
            pipe(exe[i].pipe);
		if (!check_cmd(exe[i].cmd[0]))
			exe[i].path = find_path(exe[i].cmd[0], g_data);
		else
			exe[i].path = NULL;
		i++;
	}
	return(exe);
}
