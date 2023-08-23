/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:02:20 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/23 18:05:21 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft.h"
# include "./ft_printf.h"
# include "./get_next_line.h"
# include "./ft_malloc.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <signal.h>
# include <termios.h>

# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define RESET		"\x1b[0m"

typedef enum e_error_code
{
	VALID,
	MALLOC_ERR,
	QLAWI_ERR,
	ARGC_ERR,
}	t_error;

enum e_token
{
	TK_DOLLAR			= '$',
	TK_S_QUOTE			= '\'',
	TK_D_QUOTE			= '"',
	TK_LESS				= '<',
	TK_GREATER			= '>',
	TK_PIPE				= '|',
	TK_QUESTION_MARK	= '?',
	TK_SPACE			= ' ',
	TK_NEW_LINE			= '\n',
	TK_UNDERSCORE		= '_',
	TK_HYPHEN			= '-',
	TK_PERIOD			= '.',
	TK_TAB				= '\t'
};

typedef struct s_exe
{
	size_t				index;
	char				**cmd;
	char				*path;
	int					fd_in;
	int					fd_out;
	int					pipe[2];
	pid_t				*pids;
}	t_exe;

int		g_exit_status;

char	*ms_swapstr(char *src, char *swap, size_t *ints, t_data *g_data);
char	*get_q(char *str, size_t tk_count, t_data *g_data);
int		ms_open(char **str, char token, t_data *g_data, int i);
size_t	ms_count_char(char *input, char c);
int		ms_quote_skip(char *str, size_t i, char token);
char	*ms_getenv(char *str, t_data *g_data);

char	**ms_split(char **str, t_data *g_data);

char	*ms_expention(char *input, t_data *g_data);

void	launch(t_exe *exe, t_data *g_data);

t_exe	*ms_init(char *input, t_data *g_data);

void	ms_exit(t_error err);

int		check_cmd(char *cmd);
char	*find_path(char *cmd, t_data *g_data);
int     heredoc_handler(char **str, int index, int i, int ff, t_data *g);
int		expend_dollar(char **str, int i, bool flag, t_data *g_data);
void	close_pipe(int *fd);
void	dup_in_out(int *fd, int *fd_prev);
void	ft_unset(t_exe *exe, int flag, t_data *g_data);
void	ft_pwd(t_exe *exe, int flag, t_data *g_data);
void	ft_export(t_exe *exe, int flag, t_data *g_data);
void	ft_env(t_exe *exe, int flag, t_data *g_data);
void	ft_echo(t_exe *exe, int flag);
void	ft_cd(t_exe *exe, int flag, t_data *g_data);
int		ev_input_check(t_exe *exe);
char	**copy_envp(char **envp, t_data *g_data);
void	init_sig(struct sigaction *sa);
void	child_p(void);

int		termios_echoback(bool echo_ctl_chr);
void	ms_clean(char **str, t_data *g_data);

#endif