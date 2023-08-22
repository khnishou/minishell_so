/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykerdel <ykerdel@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:06:07 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/20 21:25:41 by ykerdel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_malloc.h"

t_memlist	*lst_new(void *ptr, size_t size)
{
	t_memlist	*tmp;

	tmp = (t_memlist *)malloc(sizeof(t_memlist));
	if (tmp == NULL)
		return (NULL);
	tmp->adr = ptr;
	tmp->size = size;
	tmp->next = NULL;
	return (tmp);
}

void	ft_addlst(t_memlist **lst, t_memlist *node)
{
	t_memlist	*tmp;

	tmp = *lst;
	if (tmp == NULL)
		*lst = node;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

void	*ft_malloc(t_memlist **lst, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	ft_addlst(lst, lst_new(ptr, size));
	return (ptr);
}

void	free_lst(t_memlist **lst)
{
	t_memlist	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->adr);
		(*lst)->next = NULL;
		free(*lst);
		*lst = tmp;
	}
}
