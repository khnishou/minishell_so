/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:52:38 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/04 23:07:03 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_exe *ms_init(char *input)
{
	t_exe	*exe;
	size_t	i;

	exe = (t_exe *) ft_malloc(&(g_data.mem_list), sizeof(t_exe) * (g_data.nb_pipe + 1));
	if (!exe)
		ms_exit(MALLOC_ERR);
	input = ms_expention(input);
	i = 0;
	while (i <= (size_t)g_data.nb_pipe)
	{
		exe[i].index = i;
		exe[i].fd_in = ms_open(&input, TK_LESS);
		exe[i].fd_out = ms_open(&input, TK_GREATER);
		exe[i].cmd = ms_split(&input);
		if (i != (size_t)g_data.nb_pipe)
            pipe(exe[i].pipe);
		if (!check_cmd(exe[i].cmd[0]))
			exe[i].path = find_path(exe[i].cmd[0]);
		else
			exe[i].path = NULL;
		i++;
	}
	return(exe);
}
