/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:23:57 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/26 20:02:13 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	init_g(char **envp, char *input, t_data *g_data)
{
	g_data->nb_pipe = ms_count_char(input, TK_PIPE);
	if (!g_data->envp)
	{
		g_data->envp = copy_envp(envp, g_data);
		g_exit_status = 0;
	}
}

char	*ms_read_line(t_data *g_data)
{
	char	*input;
	char	*read_line;

	read_line = readline("➜  ");
	input = ft_strtrim(read_line, " \t", g_data);
	free (read_line);
	return (input);
}

static void	shell_loop(char **envp, t_data *g_data)
{
	char	*input;
	char	*read_line;
	t_exe	*exe;

	while (true)
	{
		ft_printf(MAGENTA);
		termios_echoback(false);
		if (isatty(fileno(stdin)))
			input = ms_read_line(g_data);
		if (input && input[0])
		{
			if (!ft_strncmp(input, "exit", ft_strlen("exit") + 1))
				break ;
			add_history(input);
			init_g(envp, input, g_data);
			exe = ms_init(input, g_data);
			if (!exe)
				ms_exit(QLAWI_ERR);
			launch(exe, g_data);
		}
		else if (input == NULL)
			break ;
	}
	ft_printf(RESET);
}

int	main(int argc, char *argv[], char *envp[])
{
	struct sigaction	sa;
	t_data				g_data;

	g_data.envp = NULL;
	init_sig(&sa);
	(void) argv;
	if (argc != 1)
		printf(RED"args will be ignored\n\n"RESET);
	shell_loop(envp, &g_data);
	free_lst(&(g_data.mem_list));
	system("leaks minishell");
	return (0);
}
