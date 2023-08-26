/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 13:26:17 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/27 00:31:46 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <limits.h>
# include "./ft_malloc.h"

typedef struct s_data
{
	char		**envp;
	int			nb_pipe;
	bool		h_flag;
	t_memlist	*mem_list;
}	t_data;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

//				ft_is
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);

//				ft_mem
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size, t_data *g_data);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memset(void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);

//				ft_put
void			ft_putstr_fd(char *s, int fd);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);

//				ft_str
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
size_t			ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t size);
char			*ft_strnstr(const char	*str, const char *to_find, size_t len);
unsigned int	ft_strlcpy(char *dest, const char *src, unsigned int size);
unsigned int	ft_strlcat(char *dest, const char *src, unsigned int size);
char			*ft_strjoin(char *s1, char *s2, t_data *g_data);
char			*ft_strtrim(char const *s, char const *set, t_data *g_data);
char			*ft_strdup(const char *s, t_data *g_data);
char			*ft_substr(char const *s, unsigned int t, size_t l, t_data *g);
char			**ft_split(char const *s, char c, t_data *g_data);
char			*ft_strmapi(char const *s, char (*f)
					(unsigned int, char), t_data *g);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));

//				ft_to
int				ft_tolower(int str);
int				ft_toupper(int str);
char			*ft_itoa(int n, t_data *g_data);

char			*ft_delsep(char *str, t_data *g_data);

#endif