/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:54:38 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/29 19:42:12 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	run_cmd(t_exe *exe, int flag, t_data *g)
{
	if (!ft_strncmp(exe->cmd[0], "cd", ft_strlen("cd") + 1))
		bd_cd(exe, flag, g);
	else if (!ft_strncmp(exe->cmd[0], "pwd", ft_strlen("pwd") + 1))
		bd_pwd(exe, flag, g);
	else if (!ft_strncmp(exe->cmd[0], "export", ft_strlen("export") + 1))
		bd_export(exe, flag, g);
	else if (!ft_strncmp(exe->cmd[0], "unset", ft_strlen("unset") + 1))
		bd_unset(exe, flag, g);
	else if (!ft_strncmp(exe->cmd[0], "env", ft_strlen("env") + 1))
		bd_env(exe, flag, g);
	else if (!ft_strncmp(exe->cmd[0], "echo", ft_strlen("echo") + 1))
		bd_echo(exe, flag);
	else if (!ft_strncmp(exe->cmd[0], "exit", ft_strlen("exit") + 1))
		bd_exit(exe, g);
	else
		ft_printf("%s: command not found\n", exe->cmd[0]);
}

static void	execute_command(t_exe *exe, t_exe *exe_prev, t_data *g)
{
	child_p();
	if (exe_prev)
	{
		dup2(exe_prev->pipe[0], 0);
		close(exe_prev->pipe[1]);
	}
	if (exe->fd_in)
	{
		dup2(exe->fd_in, 0);
		close(exe->fd_in);
		if (exe->h_flag)
			unlink(ft_strjoin("obj/.", ft_itoa(exe->index, g), g));
	}
	if (exe->fd_out)
	{
		dup2(exe->fd_out, 1);
		close(exe->fd_out);
	}
	if (check_cmd(exe->cmd[0]))
		run_cmd(exe, 1, g);
	else if (execve(exe->path, exe->cmd, g->envp) == -1)
	{
		g_exit_status = errno;
		exit(1);
	}
}

static void	child_process(t_exe *exe, int i, t_data *g)
{
	int	j;

	if (!i)
		dup2(exe[i].pipe[1], STDOUT_FILENO);
	else if (i == g->nb_pipe)
		dup2(exe[i - 1].pipe[0], STDIN_FILENO);
	else
		dup_in_out(exe[i].pipe, exe[i - 1].pipe);
	j = -1;
	while (++j < g->nb_pipe)
		close_pipe(exe[j].pipe);
	if (i > 0)
		execute_command(&exe[i], &exe[i - 1], g);
	else
		execute_command(&exe[i], NULL, g);
}

static void	exe_helper(t_exe *exe, t_data *g, int i)
{
	exe->pids[i] = fork();
	if (exe->pids[i] == -1)
	{
		g_exit_status = errno;
		exit(1);
	}
	else if (exe->pids[i] == 0)
	{
		if (!(g->nb_pipe))
			execute_command(&exe[i], NULL, g);
		else
			child_process(exe, i, g);
	}
	else if (i > 0)
		close_pipe(exe[i - 1].pipe);
}

void	launch(t_exe *exe, t_data *g)
{
	int	i;

	i = -1;
	exe->pids = ft_malloc(&g->mem_list, sizeof(pid_t) * (g->nb_pipe + 1));
	if (g->nb_pipe == 0 && check_cmd(exe[0].cmd[0]))
		run_cmd(exe, 0, g);
	else
	{
		while (++i <= g->nb_pipe)
			exe_helper(exe, g, i);
		i = -1;
		while (++i <= g->nb_pipe)
			waitpid(exe->pids[i], NULL, 0);
	}
}
