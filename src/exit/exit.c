/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:54:42 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/16 20:08:37 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    ms_exit(t_error err)
{
    if (err == VALID)
        exit (0);
    if (err == ARGC_ERR)
        ft_printf(RED"Please don't overflow me\n"RESET);
    if (err == MALLOC_ERR)
        ft_printf(RED"Malloc fail\n"RESET);
    exit (1);
}
void	ft_exit(void)
{
	free_lst(&(g_data.mem_list));
	exit(g_data.exit_status);
}
void    builtin_exit(t_exe *exe, int flag)
{
    int     nbr;
    char    *tmp;
    int     len;

    len = -1;
    g_data.exit_status = 1;
    while (exe->cmd[++len])
        ;
    if (len == 2)
    {
        nbr = ft_atoi(exe->cmd[i]);
        tmp = ft_itoa(nbr);
        if (!ft_strncmp(exe->cmd[i], tmp, ft_strlen(exe->cmd[i]))
            && !ft_strncmp(exe->cmd[i], tmp, ft_strlen(tmp)))
            g_data.exit_status = nbr;
        else
            g_data.exit_status = 255;
        if (flag)
            ft_exit();
    }
    else
    {
        if (len > 2)
        {
            ft_printf("too many arguments\n");
            g_data.exit_status = 1;
        }
        if (flag)
            ft_exit();
    }
    
}
