/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_erase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 16:15:45 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/09 17:00:53 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

void	*erasehash(void **item)
{
	char	**t;

	t = (char**)*item;
	if (!t)
		return (0);
	ft_memdel((void**)&t[0]);
	ft_memdel((void**)&t[1]);
	ft_memdel((void**)&t);
	return (0);
}

void	btree_erase(t_btree **root, void *erase(void **))
{
	if (!root || !*root)
		return ;
	if ((*root)->left)
		btree_erase(&((*root)->left), erase);
	if ((*root)->right)
		btree_erase(&((*root)->right), erase);
	erase(&((*root)->item));
	free(*root);
	*root = 0;
}

void	erase_hash_tab(t_btree **hash_tb)
{
	long	i;

	i = -1;
	while (++i < HASH_SIZE)
		btree_erase(&hash_tb[i], erasehash);
	ft_memdel((void**)&hash_tb);
}
