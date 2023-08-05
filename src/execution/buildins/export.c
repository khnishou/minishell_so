/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 05:21:58 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/05 17:17:41 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"


void	ft_export(t_exe *exe)
{
	int		nb_arg;
	char	**val;
	char	**new_ev;
	int		i;
	int		size;

	if (!ev_input_check(exe))
	{
		// invalid input format error msg
		return ;
	}
	nb_arg = 0;
	while (exe->cmd[nb_arg])
		nb_arg++;
	if (nb_arg - 1 == 0)
		ft_env(exe);
	else
	{
		i = -1;
		while (g_data.envp[++i])
			;
		size = i + nb_arg;
		new_ev = malloc(sizeof(char *) * (size + 1));
		if (new_ev == NULL)
		{
			//error 
			return ;
		}
		i = -1;
		while (g_data.envp[++i])
			new_ev[i] = ft_strdup(g_data.envp[i]);
		nb_arg = 1;
		while (exe->cmd[nb_arg])
		{
			new_ev[i] = ft_strdup(exe->cmd[nb_arg]);
			i++;
			nb_arg++;
		}
		new_ev[i] = NULL;
		g_data.envp = new_ev;
	}
}
