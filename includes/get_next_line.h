/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:04:47 by ykerdel           #+#    #+#             */
/*   Updated: 2023/06/17 10:45:25 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8192
# endif

size_t			gnl_strlen(const char *s);
char			*gnl_strjoin(char *s1, char *s2);
char			*gnl_strchr(const char *s, int c);
char			*gnl_substr(char *s, unsigned int start, double len);
char			*get_next_line(int fd);

#endif