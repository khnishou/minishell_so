/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:54:42 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/21 17:20:14 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ms_exit(t_error err)
{
	if (err == ARGC_ERR)
		ft_printf(RED"Please don't overflow me\n"RESET);
	if (err == MALLOC_ERR)
		ft_printf(RED"Malloc fail\n"RESET);
}
