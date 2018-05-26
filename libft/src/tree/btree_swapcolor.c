/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_swapcolor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 14:34:08 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/08 14:36:05 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	btree_swapcolor(t_btree *a, t_btree *b)
{
	enum e_rb_color	tmp;

	if (!a || !b)
		return ;
	tmp = a->color;
	a->color = b->color;
	b->color = tmp;
}
