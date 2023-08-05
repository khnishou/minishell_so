/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 05:22:02 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/05 15:52:56 by smallem          ###   ########.fr       */
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

void	ft_unset(t_exe *exe)
{
	char	**new_ev;
	int		size;
	int		i;
	int		nb_arg;

	i = -1;
	while (g_data.envp[++i])
		;
	nb_arg = 1;
	while (exe->cmd[nb_arg])
		nb_arg++;
	size = i - nb_arg + 1;
	new_ev = malloc(sizeof(char *) * size);
	if (new_ev == NULL)
	{
		//error
		return ;
	}
	i = 0;
	nb_arg = 0;
	while (g_data.envp[i] && nb_arg < size)
	{
		if (ft_skip(g_data.envp[i], exe->cmd))
			i++;
		else
			new_ev[nb_arg++] = ft_strdup(g_data.envp[i++]);
	}
	new_ev[nb_arg] = NULL;
	g_data.envp = new_ev;
}
