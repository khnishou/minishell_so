/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 05:21:54 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/05 14:53:38 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_env(t_exe *exe, t_data *g_data)
{
	int	i;

	i = 0;
	while (g_data->envp[i])
	{
		ft_printf("%s\n", g_data->envp[i]);
		i++;
	}
	g_data->exit_status = 0;
}
