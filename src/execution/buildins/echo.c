/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 05:21:49 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/16 19:07:38 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static	int	skip(t_exe *exe)
{
	int	flag;
	int	i;

	i = 1;
	if (exe->cmd[1][0] == '-' && exe->cmd[1][1] != 'n')
		return (-1);
	if (!ft_strncmp(exe->cmd[1], "-n", ft_strlen("-n")))
	{
		while (exe->cmd[i] && !ft_strncmp(exe->cmd[i], "-n", ft_strlen("-n")))
			i++;
	}
	return (i);
}

void	ft_echo(t_exe *exe, int flag)
{
	int		len;
	int		i;
	bool	no_new_line;

	len = -1;
	i = 1;
	no_new_line = false;
	g_data.exit_status = 0;
	while (exe->cmd[++len])
		;
	if (len == 1)
	{
		ft_printf("\n");
		return ;
	}
	while(i < len)
	{
		if (i == 1 && !ft_strncmp(exe->cmd[i], "-n", ft_strlen("-n") + 1))
		{
			i = skip(exe);
			if (i < 0)
			{
				g_data.exit_status = 1;
				if (flag)
					ft_exit();
				else
					return ;
			}
			i--;
			no_new_line = true;
		}
		else
		{
			if (i == len - 1)
				ft_printf("%s", exe->cmd[i]);
			else
				ft_printf("%s ", exe->cmd[i]);
		}
		i++;
	}
	if (no_new_line == false)
		ft_printf("\n");
	if (flag)
		ft_exit();
}
