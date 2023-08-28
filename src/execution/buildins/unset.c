/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 05:22:02 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/27 20:01:45 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	ft_skip(char *ev_line, char **cmd)
{
	int	i;

	i = 0;
	while (cmd[++i])
	{
		if (!ft_strncmp(cmd[i], ev_line, ft_strlen(cmd[i])))
			return (1);
	}
	return (0);
}

static char	**ft_unset2(int *fc, t_exe *exe, int flag, t_data *g)
{
	char	**new_ev;

	new_ev = ft_malloc(&g->mem_list, sizeof(char *) * fc[0]);
	if (new_ev == NULL)
	{
		if (flag)
			exit(1);
		else
		{
			g_exit_status = 1;
			return (NULL);
		}
	}
	fc[1] = 0;
	fc[2] = 0;
	while (g->envp[fc[1]] && fc[2] < fc[0])
	{
		if (ft_skip(g->envp[fc[1]], exe->cmd))
			fc[1]++;
		else
			new_ev[fc[2]++] = ft_strdup(g->envp[fc[1]++], g);
	}
	new_ev[fc[2]] = NULL;
	return (new_ev);
}

void	ft_unset(t_exe *exe, int flag, t_data *g)
{
	char	**new_ev;
	int		fc[3];

	if (exe->cmd[1] == NULL || !ms_getenv(exe->cmd[1], g))
	{
		if (flag)
			exit(1);
		else
			return ;
	}
	fc[1] = 0;
	while (g->envp[fc[1]])
		fc[1]++;
	fc[2] = 1;
	while (exe->cmd[fc[2]])
		fc[2]++;
	fc[0] = fc[1] - fc[2] + 1;
	g->envp = ft_unset2(fc, exe, flag, g);
	if (!(g->envp))
		return ;
	g_exit_status = 0;
	if (flag)
		exit(0);
}
