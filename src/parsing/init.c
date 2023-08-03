/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:52:38 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/03 05:23:03 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_exe *ms_init(char *input, t_data *g_data)
{
	t_exe	*exe;
	size_t	i;

	exe = (t_exe *) malloc(sizeof(t_exe) * (g_data->nb_pipe + 1));
	if (!exe)
		ms_exit(MALLOC_ERR);
	input = ms_expention(input, &g_data->exit_status);
	i = 0;
	while (i <= (size_t)g_data->nb_pipe)
	{
		exe[i].index = i;
		exe[i].fd_in = ms_open(&input, TK_LESS, &g_data->exit_status);
		exe[i].fd_out = ms_open(&input, TK_GREATER, &g_data->exit_status);
		exe[i].cmd = ms_split(&input);
		if (i != (size_t)g_data->nb_pipe)
            pipe(exe[i].pipe);
		if (!check_cmd(exe[i].cmd[0]))
			exe[i].path = find_path(exe[i].cmd[0], g_data);
		else
			exe[i].path = NULL;
		i++;
	}
	free(input);
	return(exe);
}
