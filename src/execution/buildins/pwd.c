/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:14:35 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/16 19:10:22 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_pwd(t_exe *exe, int flag)
{
	char	cwd[1024];

	g_data.exit_status = 0;
	if (exe->cmd[1] != NULL)
	{
		g_data.exit_status = 1;
		if (exe->cmd[1][0] == '-')
			ft_printf("bad option:\n");
		else
			ft_printf("too many arguments\n");
		if (flag)
			ft_exit();
		else
			return ;
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_printf("%s\n", cwd);
		g_data.exit_status = 0;
	}
	else
		g_data.exit_status = errno;
	if (flag)
		ft_exit();
}
