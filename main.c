/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 17:01:25 by ykerdel           #+#    #+#             */
/*   Updated: 2023/07/22 18:21:47 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_data	g_data;

void	init_g(t_data	*g_data, char **envp, char *input)
{
	g_data->nb_pipe = ms_count_char(input, TK_PIPE);
	g_data->exit_status = 0;
	g_data->envp = envp;
}

static void    shell_loop(char **envp)
{
	char	*input;
	t_exe	*exe;

	while (true)
	{
		printf(MAGENTA);
		if (!isatty(fileno(stdin)))
			input = ft_strtrim(get_next_line(fileno(stdin)), " \t");
		else
			input = ft_strtrim(readline("➜  "), " \t");
		printf(RESET);
		if (!input || !ft_strtrim(input," ")[0])
			printf(BLUE"Please feed me :/\n"RESET);
		else
			add_history(input);
		init_g(&g_data, envp, input);
		exe = ms_init(input, &g_data);
		if (!exe)
			ms_exit(QLAWI_ERR);
		launch(exe, &g_data);
		//////////////////////////////
		// ms_free();
	}
}

int main(int argc, char *argv[], char *envp[])
{
	(void)argv;
	if (argc != 1)
		printf(RED"args will be ignored\n\n"RESET);
	shell_loop(envp);
	return (0);
}
