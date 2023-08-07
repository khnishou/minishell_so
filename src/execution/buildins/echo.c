/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 05:21:49 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/07 12:51:45 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_echo(t_exe *exe, int flag)
{
	int	i;

	i = -1;
	while (exe->cmd[++i])
		;
	if (i != 2 && i != 3)
	{
		// add error message, invalid number of args
		g_data.exit_status = 1;
		if (flag)
			exit(1);
		else
			return ;
	}
	if (i == 2)
		ft_printf("%s\n", exe->cmd[1]);
	else if (!ft_strncmp(exe->cmd[1], "-n", ft_strlen("-n")) && exe->cmd[2])
		ft_printf("%s", exe->cmd[2]);
	else
	{
		// invalid option error msg
		g_data.exit_status = 1;
	}
	if (flag)
		exit(0);
}
