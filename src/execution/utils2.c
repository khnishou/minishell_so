/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:50:30 by smallem           #+#    #+#             */
/*   Updated: 2023/08/27 20:37:31 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**copy_envp(char **envp, t_data *g_data)
{
	char	**ev;
	int		i;

	i = -1;
	while (envp[++i])
		;
	ev = ft_malloc(&g_data->mem_list, sizeof(char *) * (i + 1));
	ev[i] = NULL;
	i = -1;
	while (envp[++i])
		ev[i] = ft_strdup(envp[i], g_data);
	return (ev);
}

int	ev_input_check(t_exe *exe)
{
	int	i;
	int	j;

	i = 1;
	while (exe->cmd[i])
	{
		j = 0;
		if (!ft_isalpha(exe->cmd[i][0]))
			return (0);
		while (exe->cmd[i][j] != '=')
		{
			if (!ft_isalnum(exe->cmd[i][j]) && exe->cmd[i][j] != '_')
				return (0);
			else
				j++;
		}
		i++;
	}
	return (1);
}

int	ms_tablen(char **tab)
{
	int	i;

	i = 0;
	if (tab)
		while (tab[i])
			i++;
	return (i);
}
