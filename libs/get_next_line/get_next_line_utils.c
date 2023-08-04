/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 14:22:40 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/04 22:59:38 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static unsigned int	gnl_strlcpy(char *dest, const char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	lsrc;

	lsrc = 0;
	while (src[lsrc] != '\0')
		lsrc++;
	if (size > 0)
	{
		i = 0;
		while (i < size - 1 && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (lsrc);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*d;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = 0;
	}
	s1_len = gnl_strlen(s1);
	s2_len = gnl_strlen(s2);
	d = malloc (s1_len + s2_len + 1);
	if (!d)
	{
		free(s1);
		return (NULL);
	}
	gnl_strlcpy (d, s1, s1_len + 1);
	gnl_strlcpy (d + s1_len, s2, s2_len + 1);
	free(s1);
	return (d);
}

char	*gnl_strchr(const char *s, int c)
{
	size_t	i;
	char	cc;

	i = 0;
	cc = (char) c;
	while (s[i] != '\0')
	{
		if (s[i] == cc)
			return ((char *) s + i);
		i++;
	}
	if (cc == s[i])
		return ((char *) s + i);
	return (NULL);
}

char	*gnl_substr(char *s, unsigned int start, double len)
{
	char	*d;
	double	size;

	if (start >= gnl_strlen (s))
		return (0);
	else if (gnl_strlen(s) - start < (size_t) len)
		size = gnl_strlen(s) - start;
	else
		size = len;
	d = malloc (size + 1);
	if (!d)
		return (0);
	gnl_strlcpy(d, s + start, len + 1);
	return (d);
}
