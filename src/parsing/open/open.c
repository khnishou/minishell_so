/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:54:56 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/22 17:37:27 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	single_redirect(char **str, int *ints, char token, t_data *g_data)
{
	int	start;
	int	i;

	i = ints[0];
	i++;
	if (ints[1] > 0)
		close(ints[1]);
	while ((*str)[i] && (*str)[i] == TK_SPACE)
		i++;
	if ((*str)[i] == TK_PIPE)
		return (-2);
	start = i;
	while ((*str)[i] && (ft_isalnum((*str)[i]) || (*str)[i] == TK_PERIOD ||
			(*str)[i] == TK_HYPHEN || (*str)[i] == TK_UNDERSCORE))
		i++;
	if (token == TK_GREATER)
		ints[1] = open(ft_substr(*str, start, i - start, g_data),
				O_RDWR | O_TRUNC | O_CREAT, 0000644);
	else if (token == TK_LESS)
		ints[1] = open(ft_substr(*str, start, i - start, g_data), O_RDONLY);
	if (ints[1] == -1)
		perror("Minishell");
	ints[1] = i - ints[0];
	*str = ms_swapstr(*str, NULL, (size_t *)ints, g_data);
	return (ints[1]);
}

int	append_handler(char **str, int index, t_data *g_data)
{
	size_t	ints[2];
	int		fd;
	char	*file_name;

	ints[1] = index;
	ints[1] += 2;
	while ((*str)[ints[1]] && (*str)[ints[1]] == TK_SPACE)
		ints[1]++;
	if ((*str)[ints[1]] == TK_PIPE)
		return (-1);
	ints[0] = ints[1];
	while ((*str)[ints[1]] && (ft_isalnum((*str)[ints[1]]) ||
				(*str)[ints[1]] == TK_PERIOD ||
				(*str)[ints[1]] == TK_HYPHEN ||
				(*str)[ints[1]] == TK_UNDERSCORE))
		ints[1]++;
	file_name = ft_substr(*str, ints[0], ints[1] - ints[0], g_data);
	ms_clean(&file_name, g_data);
	fd = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0000644);
	if (fd == -1)
		perror("Minishell");
	ints[0] = index;
	ints[1] = ints[1] - index;
	*str = ms_swapstr(*str, NULL, ints, g_data);
	return (fd);
}

int	double_redirect(char **str, size_t index, char token, t_data *g_data)
{
	int	i;
	int	fd;

	i = index + 2;
	while ((*str)[i] && (*str)[i] == TK_SPACE)
		i++;
	if ((*str)[i] == TK_PIPE)
		return (-2);
	if (token == TK_GREATER)
		fd = append_handler(str, index, g_data);
	else if (token == TK_LESS)
		fd = heredoc_handler(str, index, g_data);
	return (fd);
}

int	ms_open(char **str, char token, t_data *g_data)
{
	int	ints[2];

	ints[0] = 0;
	ints[1] = 0;
	while ((*str)[ints[0]] && (*str)[ints[0]] != TK_PIPE)
	{
		if ((*str)[ints[0]] == token)
		{
			if ((*str)[ints[0] + 1] && (*str)[ints[0] + 1] == token)
			{
				if (ints[1] > 0)
					close(ints[1]);
				ints[1] = double_redirect(str, ints[0], token, g_data);
			}
			else
				ints[1] = single_redirect(str, ints, token, g_data);
		}
		if (*str == NULL)
			*str = ft_strdup("", g_data);
		// the two lines above keep it from segfaulting, something is happening with ur swapstr
		// in the previous version at this point *str is an empty string but in this version 
		// *str is null, so im dupping empty string and its no longer segfaulting
		// so up 2 u how u wanna deal with this
		ints[0]++;

	}
	return (ints[1]);
}
