/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 16:48:09 by ykerdel           #+#    #+#             */
/*   Updated: 2023/07/30 16:55:14 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_memlist
{
	void					*adr;
	size_t					size;
	struct s_memlist		*next;
}				t_memlist;

void	*add_mem_block(void **p_head, size_t size);
void	remove_mem_block(void **p_head, void *ptr);
void	*my_malloc(void **p_head, size_t size);
void	my_free(void **p_head, void *adresse);
void	free_all_mem(void **p_head);
void	display_memory(void *p_head);

#endif