/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:54:38 by ykerdel           #+#    #+#             */
/*   Updated: 2023/07/22 18:45:21 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	first_proc(t_data *g_data, t_exe *exe)
{
	dup2(exe->fd_in, 0);
	dup2(exe->fd_out, 1);
	dup2(exe->pipe[1], 1);

	if (execve(exe->path, exe->cmd, g_data->envp) == -1)
	{
		g_data->exit_status = errno;
		exit(1);
	}
}

static void	mid_proc(t_data *g_data, t_exe *exe)
{
	dup2(exe->fd_in, 0);
	dup2((exe - 1)->pipe[0], 0);
	dup2(exe->fd_out, 1);
	dup2(exe->pipe[1], 1);

	if (execve(exe->path, exe->cmd, g_data->envp) == -1)
	{
		g_data->exit_status = errno;
		exit(1);
	}
}

static void	last_proc(t_data *g_data, t_exe *exe)
{
	dup2((exe - 1)->pipe[0], 0);
	dup2(exe->fd_in, 0);
	dup2(exe->fd_out, 1);

	if (execve(exe->path, exe->cmd, g_data->envp) == -1)
	{
		g_data->exit_status = errno;
		exit(1);
	}
}

void	launch(t_exe *exe, t_data *g_data)
{
	int	i;
	int	status;

	i = -1;
	while (++i <= g_data->nb_pipe)
	{
		exe[i].pid = fork();
		if (exe[i].pid == -1)
		{
			g_data->exit_status = errno;
			// to handle 
		}
		if (i == 0 && exe[i].pid == 0)
			first_proc(g_data, exe + i);
		else if (i == g_data->nb_pipe && exe[i].pid == 0)
			last_proc(g_data, exe + i);
		else if (exe[i].pid == 0)
			mid_proc(g_data, exe + i);
		waitpid(exe[i].pid, &status, 0);
	}
}
