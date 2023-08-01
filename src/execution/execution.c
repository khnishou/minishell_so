/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:54:38 by ykerdel           #+#    #+#             */
/*   Updated: 2023/07/31 20:44:35 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void execute_command(t_data *g_data, t_exe *exe, t_exe *exe_prev)
{
    if (exe_prev)
    {
        dup2(exe_prev->pipe[0], 0);
        close(exe_prev->pipe[1]);
    }
    if (exe->fd_in)
    {
        dup2(exe->fd_in, 0);
        close(exe->fd_in);
    }
    if (exe->fd_out)
    {
        dup2(exe->fd_out, 1);
        close(exe->fd_out);
    }
    if (execve(exe->path, exe->cmd, g_data->envp) == -1)
    {
        g_data->exit_status = errno;
        exit(1);
    }
}
void launch(t_exe *exe, t_data *g_data)
{
    int i;
    pid_t   pid;
    pid_t   pids[g_data->nb_pipe + 1];
    int flag;
    i = -1;
    if (g_data->nb_pipe > 0)
        flag = 1;
    while (++i <= g_data->nb_pipe)
    {
        pid = fork();
        if (pid == -1)
        {
            g_data->exit_status = errno;
            exit(1);
        }
        if (pid == 0)
        {
            if (flag)
            {
                if (i == 0)
                {
                    if (g_data->nb_pipe > 0)
                    {
                        dup2(exe[i].pipe[1], 1);
                        close(exe[i].pipe[0]);
                    }
                }
                else
                {
                    dup2(exe[i - 1].pipe[0], 0);
                    close(exe[i - 1].pipe[1]);
                    if (i < g_data->nb_pipe)
                    {
                        dup2(exe[i].pipe[1], 1);
                        close(exe[i].pipe[0]);
                    }
                }
            }
            execute_command(g_data, &exe[i], (i > 0) ? &exe[i - 1] : NULL);
        }
        else
        {
            pids[i]= pid;
            if (i > 0)
            {
                close(exe[i - 1].pipe[0]);
                close(exe[i - 1].pipe[1]);
            }
        }
    }
    i = -1;
    while (++i <= g_data->nb_pipe)
        waitpid(pids[i], NULL, 0);
}