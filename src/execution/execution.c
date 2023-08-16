/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:54:38 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/16 19:06:56 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void run_cmd(t_exe *exe, int flag)
{
    if (!ft_strncmp(exe->cmd[0], "cd", ft_strlen("cd") + 1))
        ft_cd(exe, flag);    
    else if (!ft_strncmp(exe->cmd[0], "pwd", ft_strlen("pwd") + 1))
        ft_pwd(exe, flag);
    else if (!ft_strncmp(exe->cmd[0], "export", ft_strlen("export") + 1))
        ft_export(exe, flag);
    else if (!ft_strncmp(exe->cmd[0], "unset", ft_strlen("unset") + 1))
        ft_unset(exe, flag);
    else if (!ft_strncmp(exe->cmd[0], "env", ft_strlen("env") + 1))
        ft_env(exe, flag);
    else if (!ft_strncmp(exe->cmd[0], "echo", ft_strlen("echo") + 1))
        ft_echo(exe, flag);
    else
        ft_printf("%s: command not found\n", exe->cmd[0]);
}

static void execute_command(t_exe *exe, t_exe *exe_prev)
{
    child_p();
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
    g_data.exit_status = 0;
    if (check_cmd(exe->cmd[0]))
        run_cmd(exe, 1);
    else if (execve(exe->path, exe->cmd, g_data.envp) == -1)
    {
        g_data.exit_status = errno;
        ft_exit();
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
    
    i = -1;
    exe->pids = malloc(sizeof(pid_t) * (g_data.nb_pipe + 1));
    if (g_data.nb_pipe == 0 && check_cmd(exe[0].cmd[0]))
        run_cmd(exe, 0);
    else
    {
        while (++i <= g_data.nb_pipe)
        {
            exe->pids[i] = fork();
            if (exe->pids[i] == -1)
            {
                g_data.exit_status = errno;
                exit(1);
            }
            else if (exe->pids[i] == 0)
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
            waitpid(exe->pids[i], NULL, 0);
    }
}
