/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:01:29 by ykerdel           #+#    #+#             */
/*   Updated: 2023/07/25 14:51:26 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

static size_t	get_index_nl(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i + 1);
}

static char	*gnl_read_str(int fd, char *s)
{
	char	*d;
	ssize_t	len;
	int		fst;

	d = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!d)
		return (NULL);
	fst = 1;
	len = 1;
	while (fst || (!gnl_strchr(d, '\n') && len))
	{
		fst = 0;
		len = read(fd, d, BUFFER_SIZE);
		if (len == -1)
		{
			free (d);
			free(s);
			return (NULL);
		}
		d[len] = '\0';
		s = gnl_strjoin(s, d);
	}
	free (d);
	return (s);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*s;
	static char	*sr;
	size_t		index_nl;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	s = gnl_read_str(fd, sr);
	if (!s)
	{
		sr = NULL;
		return (NULL);
	}
	index_nl = get_index_nl(s);
	sr = gnl_substr(s, index_nl, gnl_strlen(s) - index_nl - 1);
	line = gnl_substr(s, 0, index_nl);
	free(s);
	return (line);
}
