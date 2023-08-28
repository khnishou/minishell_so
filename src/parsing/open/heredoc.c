/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 23:30:46 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/27 00:47:28 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*ms_strjoin(char *s1, char *s2, t_data *g)
{
	size_t	i;
	size_t	j;
	char	*join;

	join = ft_malloc(&(g->mem_list), ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (NULL);
	i = 0;
	j = 0;
	if (s1)
		while (s1[i])
			join[j++] = s1[i++];
	i = 0;
	if (s2)
		while (s2[i])
			join[j++] = s2[i++];
	join[j] = 0;
	free (s2);
	return (join);
}

char	*heredoc_expention(char *str, t_data *g)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == TK_DOLLAR)
			i = expend_dollar(&str, i, false, g);
		else
			i++;
	}
	return (str);
}

static int	open_heredoc(char *str, char *exit, int *fc, t_data *g)
{
	int		fd;
	char	*join;
	char	*line;

	line = NULL;
	join = NULL;
	ft_printf(GREEN);
	while (ft_strncmp(line, ft_strjoin(exit, "\n", g), ft_strlen(exit) + 1))
	{
		if (!(fc[2] - 1) && line)
			line = heredoc_expention(line, g);
		join = ms_strjoin(join, line, g);
		ft_printf("heredoc>  ");
		line = get_next_line(1);
	}
	free (line);
	fd = open(ft_strjoin("obj/.", ft_itoa(fc[3], g), g),
			O_WRONLY | O_CREAT | O_TRUNC, 0000777);
	if (fd == -1)
		return (-1);
	write(fd, join, ft_strlen(join));
	ft_printf(RED);
	return (fd);
}

int	heredoc_handler(char **str, int index, int ff, t_data *g)
{
	int		fc[4];
	char	*exit;

	fc[3] = ff;
	fc[1] = index + 2;
	while ((*str)[fc[1]] && (*str)[fc[1]] == TK_SPACE)
		fc[1]++;
	fc[0] = fc[1]--;
	fc[2] = 0;
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
	*str = ms_swapstr(*str, NULL, fc, g);
	fc[1] = open_heredoc((*str), exit, fc, g);
	close(fc[1]);
	fc[1] = open(ft_strjoin("obj/.", ft_itoa(ff, g), g), O_RDWR, 0000644);
	return (fc[1]);
}
