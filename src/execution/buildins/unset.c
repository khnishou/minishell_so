/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 05:22:02 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/17 01:49:20 by ykerdel          ###   ########.fr       */
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

void	ft_unset(t_exe *exe, int flag, t_data *g_data)
{
	char	**new_ev;
	int		size;
	int		i;
	int		nb_arg;

	if (exe->cmd[1] != NULL)
	{
		//error nessages too many args
		if (flag)
			exit(1);
		else
			return ;
	}
	i = -1;
	while (g_data->envp[++i])
		;
	nb_arg = 1;
	while (exe->cmd[nb_arg])
		nb_arg++;
	size = i - nb_arg + 1;
	new_ev = malloc(sizeof(char *) * size);
	if (new_ev == NULL)
	{
		//error
		if (flag)
			exit(1);
		else
			return ;
	}
	i = 0;
	nb_arg = 0;
	while (g_data->envp[i] && nb_arg < size)
	{
		if (ft_skip(g_data->envp[i], exe->cmd))
			i++;
		else
			new_ev[nb_arg++] = ft_strdup(g_data->envp[i++], g_data);
	}
	new_ev[nb_arg] = NULL;
	g_data->envp = new_ev;
	exit_status = 0;
	if (flag)
		exit(0);
}
