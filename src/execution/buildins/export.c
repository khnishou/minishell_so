/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 05:21:58 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/29 19:28:23 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	**bd_export2(int *fc, t_exe *exe, int flag, t_data *g)
{
	char	**new_ev;

	fc[1] = 0;
	while (g->envp[fc[1]])
		fc[1]++;
	new_ev = ft_malloc(&g->mem_list, sizeof(char *) * (fc[1] + fc[0] + 1));
	if (new_ev == NULL)
	{
		if (flag)
		{
			g_exit_status = 1;
			exit(1);
		}
		else
			return (NULL);
	}
	fc[1] = -1;
	while (g->envp[++fc[1]])
		new_ev[fc[1]] = ft_strdup(g->envp[fc[1]], g);
	fc[0] = 1;
	while (exe->cmd[fc[0]])
		new_ev[fc[1]++] = ft_strdup(exe->cmd[fc[0]++], g);
	new_ev[fc[1]] = NULL;
	return (new_ev);
}

void	bd_export(t_exe *exe, int flag, t_data *g)
{
	int		fc[2];
	char	**val;
	char	**new_ev;

	if (!ev_input_check(exe))
	{
		if (flag)
			exit(1);
		else
			return ;
	}
	fc[0] = 0;
	while (exe->cmd[fc[0]])
		fc[0]++;
	if (fc[0] - 1 == 0)
		bd_env(exe, 0, g);
	else
	{
		g->envp = bd_export2(fc, exe, flag, g);
		if (!g->envp)
			return ;
	}
	g_exit_status = 0;
	if (flag)
		exit(g_exit_status);
}
