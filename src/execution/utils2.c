/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:32:51 by smallem           #+#    #+#             */
/*   Updated: 2023/08/05 15:36:00 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**copy_envp(char **envp)
{
	char	**ev;
	int		i;

	i = -1;
	while (envp[++i])
		;
	ev = malloc(sizeof(char *) * (i + 1));
	ev[i] = NULL;
	i = -1;
	while (envp[++i])
		ev[i] = ft_strdup(envp[i]);
	return (ev);
}

int	ev_input_check(t_exe *exe)
{
	int	i;
	int	j;

	i = 1;
	while(exe->cmd[i])	
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
