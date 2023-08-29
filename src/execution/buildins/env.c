/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 05:21:54 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/29 19:28:23 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	bd_env(t_exe *exe, int flag, t_data *g_data)
{
	int	i;

	if (exe->cmd[1] != NULL)
	{
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
	g_exit_status = 0;
	if (flag == 1)
		exit(0);
}
