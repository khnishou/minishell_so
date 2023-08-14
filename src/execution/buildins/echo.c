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
	int		len;
	int		i;
	bool	no_new_line;

	len = -1;
	i = 1;
	no_new_line = false;
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
			no_new_line = true;
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
	// if (i != 2 && i != 3)
	// {
	// 	// add error message, invalid number of args
	// 	g_data.exit_status = 1;
	// 	if (flag)
	// 		exit(1);
	// 	else
	// 		return ;
	// }
	// if (i == 2)
	// 	ft_printf("%s\n", exe->cmd[1]);
	// else if (!ft_strncmp(exe->cmd[1], "-n", ft_strlen("-n") + 1) && exe->cmd[2])
	// 	ft_printf("%s", exe->cmd[2]);
	// else
	// {
	// 	// invalid option error msg
	// 	g_data.exit_status = 1;
	// }
	if (flag)
		exit(0);
}
