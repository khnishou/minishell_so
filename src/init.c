/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:52:38 by ykerdel           #+#    #+#             */
/*   Updated: 2023/07/25 18:37:31 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static void printtab(char **tab)
// {
// 	size_t i;

// 	i = 0;
// 	printf("\n");
// 	while (tab[i])
// 	{
// 		printf("i = %zu // str=%s\n", i, tab[i]);
// 		i++;
// 	}
// 	printf("\n");
// }

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
		// exe[i].fd_in = ms_open(&input, TK_LESS);
		exe[i].fd_out = ms_open(&input, TK_GREATER);
		exe[i].cmd = ms_split(&input);
		if (pipe(exe[i].pipe) == -1)
			return (NULL);
		if (!check_cmd(exe[i].cmd[0]))
			exe[i].path = find_path(exe[i].cmd[0], g_data);
		else
			exe[i].path = NULL;
		// printf("\n---------- %zu ----------\n", i);
		// printtab(exe[i].cmd);
		i++;
	}
	free(input);
	return(exe);
}
