/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:37:47 by smallem           #+#    #+#             */
/*   Updated: 2023/08/12 17:01:28 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sig_handler(int sig_number)
{
	if (sig_number == SIGINT)
	{
		
		ft_printf("➜  ");
	}
	return ;
}

void	child_p(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	init_sig(struct sigaction *sa)
{
	sa->sa_handler = sig_handler;
	sa->sa_flags = 0;
	sigemptyset(&sa->sa_mask);
	sigaction(SIGINT, sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
