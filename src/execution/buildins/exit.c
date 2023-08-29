/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:29:30 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/29 19:49:12 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	bd_exit(t_exe *exe, t_data *g_data)
{
	int	i;

	i = -1;
	while (exe->cmd[1][++i])
	{
		if (!ft_isdigit(exe->cmd[1][i]))
		{
			ft_printf(RED"minishell: exit: %s: numeric argument required\n"CYAN, exe->cmd[1]);
			g_exit_status = 255;
			exit(g_exit_status);
		}
	}
	g_exit_status = atoi(exe->cmd[1]);
	exit(g_exit_status);
}
