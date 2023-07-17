/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 17:01:25 by ykerdel           #+#    #+#             */
/*   Updated: 2023/07/16 17:37:05 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	exit_status = 0;

static void    shell_loop()
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
		exe = ms_init(input, &exit_status);
		if (exe)
			printf("idk\n");
		
	}
}

int main(int argc, char *argv[])
{
	(void)argv;
	if (argc != 1)
		printf(RED"args will be ignored\n\n"RESET);
	shell_loop();
	return (0);
}
