/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 15:44:58 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/08 13:07:47 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_btree	*btree_create_node(void *item, int color)
{
	t_btree	*fut;

	fut = (t_btree*)ft_memalloc(sizeof(t_btree));
	fut->item = item;
	fut->color = color;
	return (fut);
}
