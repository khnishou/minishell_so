/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:54:38 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/05 17:03:52 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void run_cmd(t_exe *exe)
{
    if (!ft_strncmp(exe->cmd[0], "cd", ft_strlen("cd")))
        ft_cd(exe);    
    else if (!ft_strncmp(exe->cmd[0], "pwd", ft_strlen("pwd")))
        ft_pwd(exe);
    else if (!ft_strncmp(exe->cmd[0], "export", ft_strlen("export")))
        ft_export(exe);
    else if (!ft_strncmp(exe->cmd[0], "unset", ft_strlen("unset")))
        ft_unset(exe);
    else if (!ft_strncmp(exe->cmd[0], "env", ft_strlen("env")))
        ft_env(exe);
    else if (!ft_strncmp(exe->cmd[0], "echo", ft_strlen("echo")))
        ft_echo(exe);
    // if (!ft_strncmp(exe->cmd[0], "exit", ft_strlen("exit")))
    //     ft_exit(exe, g_data);
}

static void execute_command(t_exe *exe, t_exe *exe_prev)
{
    if (exe_prev)
    {
        dup2(exe_prev->pipe[0], 0);
        close(exe_prev->pipe[1]);                                               //
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
    if (execve(exe->path, exe->cmd, g_data.envp) == -1)
    {
        g_data.exit_status = errno;
        exit(1);
    }
}

static void    child_process(t_exe *exe, int i)
{
    int j;

    if (!i)
        dup2(exe[i].pipe[1], STDOUT_FILENO);
    else if (i == g_data.nb_pipe)
        dup2(exe[i - 1].pipe[0], STDIN_FILENO);
    else
        dup_in_out(exe[i].pipe, exe[i - 1].pipe);
    j = -1;
    while (++j < g_data.nb_pipe)
        close_pipe(exe[j].pipe);
    if (i > 0)
        execute_command(&exe[i], &exe[i - 1]);
    else
        execute_command(&exe[i], NULL);
}

void launch(t_exe *exe)
{
    int i;
    pid_t   pids[g_data.nb_pipe + 1];
    
    i = -1;
    if (g_data.nb_pipe == 0 && check_cmd(exe[0].cmd[0]))
        run_cmd(exe);
    else
    {
        while (++i <= g_data.nb_pipe)
        {
            pids[i] = fork();
            if (pids[i] == -1)
            {
                g_data.exit_status = errno;
                exit(1);
            }
            else if (pids[i] == 0)
            {
                if (!(g_data.nb_pipe))
                    execute_command(&exe[i], NULL);
                else
                    child_process(exe, i);
            }
            else if (i > 0)
                close_pipe(exe[i - 1].pipe);
        }
        i = -1;
        while (++i <= g_data.nb_pipe)
            waitpid(pids[i], NULL, 0);
    }
}
