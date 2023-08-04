/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 16:48:09 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/04 22:11:43 by ykerdel          ###   ########.fr       */
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

void	free_lst(t_memlist **lst);
void	*ft_malloc(t_memlist **lst, size_t size);

#endif