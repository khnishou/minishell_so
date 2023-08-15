/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 05:21:49 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/14 20:43:19 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_echo(t_exe *exe, int flag)
{
	int		len;
	int		i;
	bool	no_new_line;

	len = 0;
	i = 1;
	no_new_line = false;
	
	while (exe->cmd[len] != NULL)
		len++;
	if (len == 1)
	{
		ft_printf("\n");
		return ;
	}
	while(i < len)
	{
		if (!ft_strncmp(exe->cmd[1], "-n", ft_strlen("-n") + 1))
			no_new_line = true;
		else if (!ft_strncmp(exe->cmd[1], "-", ft_strlen("-")))
		{
			ft_printf("echo %s: command not found", exe->cmd[1]);
			g_data.exit_status = 127;
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
		exit(0);
}
