/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 05:21:54 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/17 01:48:56 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_env(t_exe *exe, int flag, t_data *g_data)
{
	int	i;

	if (exe->cmd[1] != NULL)
	{
		//error nessages too many args
		if (flag)
			exit(1);
		else
			return ;
	}
	i = 0;
	while (g_data->envp[i])
	{
		ft_printf("%s\n", g_data->envp[i]);
		i++;
	}
	exit_status = 0;
	if (flag == 1)
		exit(0);
}
