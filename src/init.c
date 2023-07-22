/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:52:38 by ykerdel           #+#    #+#             */
/*   Updated: 2023/07/22 18:13:46 by smallem          ###   ########.fr       */
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
// 		printf("ind = %zu str=%s\n", i, tab[i]);
// 		i++;
// 	}
// 	printf("\n");
// }

char	*ms_parsing(char *input, int *exit_status)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == TK_S_QUOTE || input[i] == TK_D_QUOTE)
			i = token_quote(&input, i, input[i], exit_status);
		else if (input[i] == TK_DOLLAR)
			i = token_dollar(&input, i, exit_status);
		else if (input[i] == TK_LESS && input[i + 1] && input[i + 1] == TK_LESS)
			i = token_heredoc(&input, i);
		else
			i++;
	}
	return (input);
}

t_exe *ms_init(char *input, t_data *g_data)
{
	t_exe	*exe;
	size_t	i;

	exe = (t_exe *) malloc(sizeof(t_exe) * (g_data->nb_pipe + 1));
	if (!exe)
		ms_exit(MALLOC_ERR);
	input = ms_parsing(input, &g_data->exit_status);
	i = 0;
	while (i <= (size_t)g_data->nb_pipe)
	{
		exe[i].index = i;
		exe[i].fd_in = ms_open(&input, TK_LESS);
		exe[i].fd_out = ms_open(&input, TK_GREATER);
		//printf("\n---------- %zu ----------\n", i);
		exe[i].cmd = ms_split(&input);
		if (!check_cmd(exe[i].cmd[0]))
			exe[i].path = find_path(exe[i].cmd[0], g_data);
		else
			exe[i].path = NULL;
		//printtab(exe[i].cmd);
		i++;
	}
	free(input);
	return(exe);
}
