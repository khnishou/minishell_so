/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 05:21:49 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/26 04:52:11 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h" 

static bool	is_option(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!(str[i] == 'n'))
			return (false);
		i++;
	}
	return (true);
}

static bool	ft_echo2(int len, int i, bool no_new_line, t_exe *exe)
{
	while (i < len)
	{
		if (is_option(exe->cmd[i]))
			no_new_line = true;
		else
			break ;
		i++;
	}
	while (i < len)
	{
		if (i == len - 1)
			ft_putstr_fd(exe->cmd[i], exe->fd_out);
		else
		{
			ft_putstr_fd(exe->cmd[i], exe->fd_out);
			ft_putstr_fd(" ", exe->fd_out);
		}
		i++;
	}
	return (no_new_line);
}

void	ft_echo(t_exe *exe, int flag)
{
	int		len;
	int		i;
	bool	no_new_line;

	if (!exe->fd_out)
		exe->fd_out = 1;
	len = 0;
	i = 1;
	no_new_line = false;
	while (exe->cmd[len] != NULL)
		len++;
	if (len == 1)
	{
		ft_putstr_fd("\n", exe->fd_out);
		return ;
	}
	no_new_line = ft_echo2(len, i, no_new_line, exe);
	if (no_new_line == false)
		ft_putstr_fd("\n", exe->fd_out);
	if (flag)
		exit(0);
}
