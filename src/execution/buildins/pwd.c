/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 16:14:35 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/17 01:49:13 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_pwd(t_exe *exe, int flag, t_data *g_data)
{
	char	cwd[1024];

	if (exe->cmd[1] != NULL)
	{
		if (exe->cmd[1][0] == '-')
			ft_printf("bad option:\n");
		else
			ft_printf("too many arguments\n");
		if (flag)
			exit(1);
		else
			return ;
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_printf("%s\n", cwd);
		exit_status = 0;
	}
	else
		exit_status = errno;
	if (flag)
		exit(0);
}
