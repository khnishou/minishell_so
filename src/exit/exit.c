/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:54:42 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/29 19:23:22 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_exit(t_error err)
{
	if (err == VALID)
		exit(g_exit_status);
	if (err == MALLOC_ERR)
		ft_printf(RED"Malloc fail\n"RESET);
}
