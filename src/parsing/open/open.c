/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:54:56 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/27 00:32:24 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	is_filename(char c)
{
	if ((ft_isalnum(c) || c == TK_PERIOD
			|| c == TK_HYPHEN || c == TK_UNDERSCORE))
		return (true);
	return (false);
}

int	single_redirect(char **str, int *fc, char token, t_data *g)
{
	int	start;
	int	i;
	int	fd;

	i = fc[0] + 1;
	if (fc[1] > 0)
		close(fc[1]);
	while ((*str)[i] && (*str)[i] == TK_SPACE)
		i++;
	if ((*str)[i] == TK_PIPE)
		return (-2);
	start = i;
	while ((*str)[i] && is_filename((*str)[i]))
		i++;
	if (token == TK_GREATER)
		fd = open(ft_substr(*str, start, i - start, g),
				O_RDWR | O_TRUNC | O_CREAT, 0000644);
	else if (token == TK_LESS)
		fd = open(ft_substr(*str, start, i - start, g), O_RDONLY);
	if (fc[1] == -1)
		perror("Minishell");
	fc[1] = i - fc[0];
	*str = ms_swapstr(*str, NULL, fc, g);
	return (fd);
}

int	append_handler(char **str, int index, t_data *g)
{
	int		ints[2];
	int		fd;
	char	*file_name;

	ints[1] = index + 2;
	while ((*str)[ints[1]] && (*str)[ints[1]] == TK_SPACE)
		ints[1]++;
	if ((*str)[ints[1]] == TK_PIPE)
		return (-1);
	ints[0] = ints[1];
	while ((*str)[ints[1]] && is_filename((*str)[ints[1]]))
		ints[1]++;
	file_name = ft_substr(*str, ints[0], ints[1] - ints[0], g);
	ms_clean(&file_name, g);
	fd = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0000644);
	if (fd == -1)
		perror("Minishell");
	ints[0] = index;
	ints[1] = ints[1] - index;
	*str = ms_swapstr(*str, NULL, ints, g);
	return (fd);
}

int	double_redirect(char **str, int *fc, char token, t_data *g)
{
	int	i;
	int	fd;

	i = fc[0] + 2;
	while ((*str)[i] && (*str)[i] == TK_SPACE)
		i++;
	if ((*str)[i] == TK_PIPE)
		return (-2);
	if (token == TK_GREATER)
		fd = append_handler(str, fc[0], g);
	else if (token == TK_LESS)
	{
		g->h_flag = true;
		fd = heredoc_handler(str, fc[0], fc[2], g);
	}
	return (fd);
}

int	ms_open(char **str, char token, t_data *g, int i)
{
	int	ints[3];

	ints[0] = 0;
	ints[1] = 0;
	ints[2] = i;
	while ((*str)[ints[0]] && (*str)[ints[0]] != TK_PIPE)
	{
		if ((*str)[ints[0]] == token)
		{
			if ((*str)[ints[0] + 1] && (*str)[ints[0] + 1] == token)
			{
				if (ints[1] > 0)
					close(ints[1]);
				ints[1] = double_redirect(str, (int *) ints, token, g);
			}
			else
				ints[1] = single_redirect(str, ints, token, g);
		}
		ints[0]++;
	}
	if (ints[1] == -1)
		g_exit_status = 1;
	return (ints[1]);
}
