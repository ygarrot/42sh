/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 11:57:58 by ygarrot           #+#    #+#             */
/*   Updated: 2018/05/17 16:39:09 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

void			delhash(void *item)
{
	if (!item)
		return ;
	ft_strdel(&((char**)item)[0]);
	ft_strdel(&((char**)item)[1]);
	free(item);
}

unsigned long	hash(char *str)
{
	unsigned long	hash;
	unsigned long	c;

	if (!str)
		return (0);
	hash = 5381;
	while ((c = (unsigned long)*str++))
		hash = ((hash << 5) + hash) + c;
	return (hash);
}

int				ft_set_hash(t_btree **begin, char *key, char *value)
{
	char	**content;
	char	**tmp;

	tmp = NULL;
	if (!begin || !*begin || !key || !value)
		return (-1);
	if (!*begin || !(tmp = btree_search_item(*begin, &key, ft_hashcmp)))
	{
		if (!(content = (char**)ft_memalloc(2 * sizeof(char*))))
			return (-1);
		content[0] = ft_strdup(key);
		content[1] = ft_strdup(value);
		btree_insert_data(begin, content, ft_hashcmp, delhash);
		return (1);
	}
	if (tmp)
	{
		ft_memdel((void**)&tmp[1]);
		tmp[1] = ft_strdup(value);
	}
	return (1);
}

char			*ft_get_hash(t_btree **hash_tb, char *key)
{
	unsigned long	index;
	char			**tmp;
	t_btree			*root;

	if (!hash_tb || !key)
		return (NULL);
	index = hash(key) % HASH_SIZE;
	if (!(root = hash_tb[index]))
		return (NULL);
	tmp = btree_search_item(root, &key, ft_hashcmp);
	return (tmp ? tmp[1] : NULL);
}
