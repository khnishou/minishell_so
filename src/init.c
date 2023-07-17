/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:52:38 by ykerdel           #+#    #+#             */
/*   Updated: 2023/07/17 16:42:59 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void printtab(char **tab)
{
	size_t i;

	i = 0;
	printf("\n");
	while (tab[i])
	{
		printf("ind = %zu str=%s\n", i, tab[i]);
		i++;
	}
	printf("\n");
}

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

t_exe *ms_init(char *input, int *exit_status)
{
	size_t	nbr_pipe;
	t_exe	*exe;
	size_t	i;
	
	nbr_pipe = ms_count_char(input, TK_PIPE);
	exe = (t_exe *) malloc(sizeof(t_exe) * (nbr_pipe + 1));
	if (!exe)
		ms_exit(MALLOC_ERR);
	input = ms_parsing(input, exit_status);
	printf("input = %s\n", input);
	i = 0;
	while (i <= nbr_pipe)
	{
		exe[i].index = i;
		exe[i].nbr_pipe = nbr_pipe;
		exe[i].fd_in = ms_open(&input, TK_LESS);
		// printf("in = %d\n",exe[i].fd_in);
		exe[i].fd_out = ms_open(&input, TK_GREATER);
		// printf("out = %d\n",exe[i].fd_out);
		// printf("size = %zu", split_size(input));
		exe[i].cmd = ms_split(&input, split_size(input));
		printf("\n---------- %zu ----------\n", i);
		printtab(exe[i].cmd);
		i++;
	}
	printf("\nstr = %s\n", input);
	free(input);
	return(NULL);
}