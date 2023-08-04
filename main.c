/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 17:01:25 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/04 23:07:56 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	init_g(char **envp, char *input)
{
	g_data.nb_pipe = ms_count_char(input, TK_PIPE);
	g_data.exit_status = 0;
	g_data.envp = envp;
}

static void    shell_loop(char **envp)
{
	char	*input;
	t_exe	*exe;

	while (true)
	{
		ft_printf(MAGENTA);
		if (!isatty(fileno(stdin)))
		{
        	ft_printf("➜  ");
			input = ft_strtrim(get_next_line(fileno(stdin)), " \t");
		}
		else
			input = ft_strtrim(readline("➜  "), " \t");
		if (input && input[0])
		{
			add_history(input);
			init_g(envp, input);
			exe = ms_init(input);
			if (!exe)
				ms_exit(QLAWI_ERR);
			launch(exe);
			free_lst(&(g_data.mem_list));
			system("leaks minishell");
		}
	}
	ft_printf(RESET);
}

int main(int argc, char *argv[], char *envp[])
{
	(void) argv;
	if (argc != 1)
		printf(RED"args will be ignored\n\n"RESET);
	shell_loop(envp);
	return (0);
}
