/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 05:21:54 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/16 19:08:46 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_env(t_exe *exe, int flag)
{
	int	i;

	if (exe->cmd[1] != NULL)
	{
		ft_printf("too many arguments\n");
		g_data.exit_status = 1;
		if (flag)
			exit(g_data.exit_status);
		else
			return ;
	}
	i = 0;
	while (g_data.envp[i])
	{
		ft_printf("%s\n", g_data.envp[i]);
		i++;
	}
	g_data.exit_status = 0;
	if (flag == 1)
		exit(g_data.exit_status);
}
