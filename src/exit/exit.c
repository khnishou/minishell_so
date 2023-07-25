/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:54:42 by ykerdel           #+#    #+#             */
/*   Updated: 2023/07/23 23:42:19 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    ms_exit(t_error err)
{
    if (err == VALID)
        exit (0);
    if (err == ARGC_ERR)
        printf(RED"Please don't overflow me\n"RESET);
    if (err == MALLOC_ERR)
        printf(RED"Malloc fail\n"RESET);
    exit (1);
}
