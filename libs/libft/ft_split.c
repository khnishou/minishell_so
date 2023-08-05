/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 18:10:31 by ykerdel           #+#    #+#             */
/*   Updated: 2023/08/05 17:58:01 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	ft_countwords(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != 0)
	{
		if (((s[i] != c) && i == 0) || ((s[i] != c) && (s[i - 1] == c)))
			count ++;
		i ++;
	}
	return (count);
}

static int	ft_countwordlen(char *s, char c)
{
	int	j;

	j = 0;
	while ((s[j] != '\0') && (s[j] != c))
		j ++;
	return (j);
}

static int	ft_copystringsintab(char *str, char c, int tab_len, char **tab)
{
	int		i;
	int		word_len;

	i = 0;
	while (*str)
	{
		if (*str != c && i < tab_len)
		{
			word_len = ft_countwordlen(str, c);
			tab[i] = (char *) ft_malloc(&(g_data.mem_list), word_len + 1);
			if (!tab[i])
			{
				while (--i >= 0)
					// free(tab[i]);
				// free(tab);
				return (0);
			}
			ft_strlcpy(tab[i], str, word_len + 1);
			i ++;
			str += (word_len - 1);
		}
		str ++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		tab_len;
	char	*str;
	int		successalloc;

	str = (char *)s;
	tab_len = ft_countwords(s, c);
	if (!tab_len)
		return ((char **)ft_calloc(1, sizeof(char *)));
	tab = (char **) ft_calloc((tab_len + 1), sizeof(char *));
	if (!tab)
		return (NULL);
	successalloc = ft_copystringsintab(str, c, tab_len, tab);
	if (successalloc)
		tab[tab_len] = NULL;
	else
		return (NULL);
	return (tab);
}
