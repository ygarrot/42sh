/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_insert_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 16:16:59 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/16 13:28:54 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	btree_insert_data_n(void *item, int val,
		t_btree *tmp)
{
	if (val > 0)
		tmp->right = btree_create_node(item);
	else
		tmp->left = btree_create_node(item);
	if (val > 0 && tmp->right)
		tmp->right->parent = tmp;
	else if (val < 0 && tmp->left)
		tmp->left->parent = tmp;
	else
		return (-1);
	return (0);
}

int			btree_insert_data(t_btree **root, void *item, int (*cmpf)(void *,
			void *), void (*del)(void *item))
{
	t_btree	*tmp;
	int		val;

	if (!root)
		return (-1);
	else if (!(tmp = *root))
		return (-!(*root = btree_create_node(item)));
	val = cmpf(item, tmp->item);
	while (val && ((tmp->left && val < 0) || (tmp->right && val > 0)))
	{
		tmp = (val < 0) ? (tmp->left) : (tmp->right);
		val = cmpf(item, tmp->item);
	}
	if (!val)
	{
		del(tmp->item);
		tmp->item = item;
		return (0);
	}
	return (btree_insert_data_n(item, val, tmp));
}
