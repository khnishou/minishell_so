/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:54:38 by ykerdel           #+#    #+#             */
/*   Updated: 2023/07/25 19:43:18 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int p[2];

static void	first_proc(t_data *g_data, t_exe *exe)
{
	// dup2(exe->fd_in, 0);
	//dup2(exe->fd_out, 1);
	// dup2(exe->pipe[1], 1);
	dup2(p[1], 1);
	// close(p[0]);
	// close(p[0]);
	if (execve(exe->path, exe->cmd, g_data->envp) == -1)
	{
		g_data->exit_status = errno;
		exit(1);
	}
}

static void	mid_proc(t_data *g_data, t_exe *exe)
{
	dup2(exe->fd_in, 0);
	ft_printf("test");
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
	// dup2((exe - 1)->pipe[0], 0);
	dup2(p[0], 0);
	//dup2(exe->fd_out, 1);
	// close(p[1]);

	//dup2(exe->fd_in, 0);
	//dup2(exe->fd_out, 1);
	if (execve(exe->path, exe->cmd, g_data->envp) == -1)
	{
		// perror("zok");
		g_data->exit_status = errno;
		exit(1);
	}
}

void	launch(t_exe *exe, t_data *g_data)
{
	int	i;
	int	status;


	pipe(p);

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
		{
			dprintf(2, "i m khnishoooo \n");
			last_proc(g_data, exe + i);
		}
		else if (exe[i].pid == 0)
			mid_proc(g_data, exe + i);
		else
		{
			// dup2(p[1], 1);
			dprintf(2, "before the waot %d\n", exe[i].pid);
			// waitpid(exe[i].pid, &status, 0);
				dprintf(2, "under wait\n");
				sleep(1);
		}
	}
	dprintf(2, "outside of looop\n");
}
	