/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 23:30:46 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/22 05:48:25 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*heredoc_expention(char *str, t_data *g_data)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == TK_DOLLAR)
			i = expend_dollar(&str, i, false, g_data);
		else
			i++;
	}
	return (str);
}

static int	open_heredoc(char *str, char *exit, int tk_count, t_data *g_data)
{
	int		fd;
	char	*join;
	char	*line;

	line = NULL;
	join = NULL;
	ft_printf(GREEN);
	while (ft_strncmp(line, ft_strjoin(exit, "\n", g_data), ft_strlen(exit) + 1))
	{
		if (!tk_count && line)
			line = heredoc_expention(line, g_data);
		join = ft_strjoin(join, line, g_data);
		ft_printf("heredoc>  ");
		line = get_next_line(1);
	}
	fd = open("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0000777);
	if (fd == -1)
	{
		perror("Error opening heredoc file");
		return (-1);
	}
	write(fd, join, ft_strlen(join));
	ft_printf(RESET);
	return (fd);
}

int	heredoc_handler(char **str, int index, t_data *g)
{
	int		fc[3];
	char	*exit;

	fc[1] = index + 2;
	while ((*str)[fc[1]] && (*str)[fc[1]] == TK_SPACE)
		fc[1]++;
	fc[0] = fc[1];
	fc[2] = 0;
	--fc[1];
	while ((*str)[++fc[1]] && (*str)[fc[1]] != ' ' && (*str)[fc[1]] != '|')
	{
		if (((*str)[fc[1]] == TK_D_QUOTE || (*str)[fc[1]] == TK_S_QUOTE))
		{
			fc[1] = ms_quote_skip((*str), fc[1], (*str)[fc[1]]);
			fc[2] += 2;
		}
	}
	exit = get_q(ft_substr((*str), fc[0], fc[1] - fc[0], g), fc[2], g);
	fc[0] = index;
	fc[1] = fc[1] - index;
	*str = ms_swapstr(*str, NULL, (size_t *)fc, g);
	fc[1] = open_heredoc((*str), exit, fc[2] - 1, g);
	close(fc[1]);
	fc[1] = open("heredoc", O_RDWR | O_TRUNC | O_CREAT, 0000644);
	return (fc[1]);
}
