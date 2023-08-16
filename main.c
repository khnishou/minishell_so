/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:23:57 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/16 17:53:02 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	init_g(char **envp, char *input)
{
	g_data.nb_pipe = ms_count_char(input, TK_PIPE);
	if (!g_data.envp)
	{
		g_data.envp = copy_envp(envp);
		g_data.exit_status = 0;
	}
}

static void    shell_loop(char **envp)
{
	char	*input;
	t_exe	*exe;
	
	while (true)
	{
		ft_printf(MAGENTA);
		termios_echoback(false);
		// if (!isatty(fileno(stdin)))
		// {
        // 	ft_printf("➜  ");
		// 	input = ft_strtrim(get_next_line(fileno(stdin)), " \t");
		// }
		// else
			input = ft_strtrim(readline("➜  "), " \t");
		if (input && input[0])
		{
			add_history(input);
			init_g(envp, input);
			exe = ms_init(input);
			if (!exe)
				ms_exit(QLAWI_ERR);
			// dprintf(2, "fd = %d\n", exe[1].fd_in);
			launch(exe);
			if (!ft_strncmp(input, "exit", ft_strlen("exit") + 1))
				break;
			//system("leaks minishell");
		}
		else if (input == NULL)
			break ;
	}
	ft_printf(RESET);
}

int main(int argc, char *argv[], char *envp[])
{
	struct sigaction	sa;

	init_sig(&sa);
	(void) argv;
	if (argc != 1)
		printf(RED"args will be ignored\n\n"RESET);
	shell_loop(envp);
	free_lst(&(g_data.mem_list));
	return (0);
}
