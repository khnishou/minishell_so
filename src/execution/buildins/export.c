/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 05:21:58 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/17 01:49:03 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"


void	ft_export(t_exe *exe, int flag, t_data *g_data)
{
	int		nb_arg;
	char	**val;
	char	**new_ev;
	int		i;
	int		size;

	if (!ev_input_check(exe))
	{
		// invalid input format error msg
		if (flag)
			exit(1);
		else
			return ;
	}
	nb_arg = 0;
	while (exe->cmd[nb_arg])
		nb_arg++;
	if (nb_arg - 1 == 0)
		ft_env(exe, 0, g_data);
	else
	{
		i = -1;
		while (g_data->envp[++i])
			;
		size = i + nb_arg;
		new_ev = malloc(sizeof(char *) * (size + 1));
		if (new_ev == NULL)
		{
			ms_exit(MALLOC_ERR); 
			if (flag)
			exit(1);
		else
			return ;
		}
		i = -1;
		while (g_data->envp[++i])
			new_ev[i] = ft_strdup(g_data->envp[i], g_data);
		nb_arg = 1;
		while (exe->cmd[nb_arg])
		{
			new_ev[i] = ft_strdup(exe->cmd[nb_arg], g_data);
			i++;
			nb_arg++;
		}
		new_ev[i] = NULL;
		g_data->envp = new_ev;
	}
	exit_status = 0;
	if (flag)
		exit(0);
}
