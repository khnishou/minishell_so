/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:54:42 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/05 18:33:21 by smallem          ###   ########.fr       */
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
