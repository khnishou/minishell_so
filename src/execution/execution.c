/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:54:38 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/03 03:13:58 by ykerdel          ###   ########.fr       */
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
    int j;
    pid_t   pids[g_data->nb_pipe + 1];
    
    i = -1;
    while (++i <= g_data->nb_pipe)
    {
        pids[i] = fork();
        if (pids[i] == -1)
        {
            g_data->exit_status = errno;
            exit(1);
        }
        else if (pids[i] == 0)
        {
            if (i == 0)
            {
                if (g_data->nb_pipe > 0)
                {
                    dup2(exe[i].pipe[1], 1);
                    close(exe[i].pipe[0]);
                    close(exe[i].pipe[1]);
                }
            }
            else
            {
                dup2(exe[i - 1].pipe[0], 0);
                close(exe[i - 1].pipe[0]);
                if (i < g_data->nb_pipe)
                {
                    close(exe[i].pipe[0]);
                    dup2(exe[i].pipe[1], 1);
                    close(exe[i].pipe[1]);
                }
            }
            j = i;
            while (++j < g_data->nb_pipe)
            {
                close(exe[j].pipe[0]);
                close(exe[j].pipe[1]);
            }
            execute_command(g_data, &exe[i], (i > 0) ? &exe[i - 1] : NULL);
        }
        else if (i > 0)
        {
            close(exe[i - 1].pipe[0]);
            close(exe[i - 1].pipe[1]);
        }
    }
    i = -1;
    while (++i <= g_data->nb_pipe)
        waitpid(pids[i], NULL, 0);
}