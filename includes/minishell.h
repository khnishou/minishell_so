/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:02:20 by ykerdel           #+#    #+#             */
/*   Updated: 2023/07/16 22:28:16 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include "./libft.h"
#include "./get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

typedef enum e_error_code
{
	VALID,
	ARGC_ERR,
	MALLOC_ERR,
}					t_error;

enum e_token
{
	TK_DOLLAR           = '$',
    TK_S_QUOTE          = '\'',
    TK_D_QUOTE          = '"',
    TK_LESS             = '<',
    TK_GREATER          = '>',
    TK_PIPE             = '|',
    TK_QUESTION_MARK    = '?',
    TK_SPACE            = ' ',
    TK_NEW_LINE         = '\n',
    TK_UNDERSCORE       = '_',
    TK_HYPHEN           = '-',
    TK_PERIOD           = '.',
    TK_TAB              = '\t'
};

typedef struct s_exe
{
    size_t              index;
    char                **cmd;
    int                 fd_in;
    int                 fd_out;
    size_t              nbr_pipe;
	int		            pipe[2];
    
}	t_exe;

char	    *ms_swapstr(char *src, char *swap, size_t start, size_t len);
char        *quote_str_get(char *str, size_t tk_count);
int         ms_open(char **str, char token);
size_t      ms_count_char(char *input, char c);

size_t	split_size(char *str);
char	    **ms_split(char **str, size_t size);

size_t      token_dollar(char **str, int index, int *exit_status);
size_t      token_quote(char **str, size_t i, char token, int *exit_status);
int         token_redirect(char **str, size_t index, int fd, char token);
int         token_append(char **str, size_t index, int fd);
size_t      token_heredoc(char **str, size_t index);


t_exe       *ms_init(char *input, int *exit_status);

void        ms_exit(t_error err);

#endif