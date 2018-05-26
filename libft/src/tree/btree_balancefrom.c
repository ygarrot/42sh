/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_balancefrom.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 13:43:31 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/08 14:48:56 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static void	btree_rotateleft(t_btree **root, t_btree *pt)
{
	t_btree	*pt_right;

	if (!pt || !(pt_right = pt->right))
		return ;
	if ((pt->right = pt_right->left))
		pt->right->parent = pt;
	pt_right->parent = pt->parent;
	if (!(pt->parent))
	{
		if (root)
			*root = pt_right;
	}
	else if (pt == pt->parent->left)
		pt->parent->left = pt_right;
	else
		pt->parent->right = pt_right;
	pt_right->left = pt;
	pt->parent = pt_right;
}

static void	btree_rotateright(t_btree **root, t_btree *pt)
{
	t_btree	*pt_left;

	if (!pt || !(pt_left = pt->left))
		return ;
	pt->left = pt_left->right;
	if (pt->left)
		pt->left->parent = pt;
	pt_left->parent = pt->parent;
	if (!(pt->parent))
	{
		if (root)
			*root = pt_left;
	}
	else if (pt == pt->parent->left)
		pt->parent->left = pt_left;
	else
		pt->parent->right = pt_left;
	pt_left->right = pt;
	pt->parent = pt_left;
}

static void	btree_parentleft(t_btree **root, t_btree **pt, t_btree *parent,
		t_btree *grand_parent)
{
	t_btree	*uncle;

	uncle = grand_parent->right;
	if (uncle && uncle->color == RB_RED)
	{
		grand_parent->color = RB_RED;
		parent->color = RB_BLACK;
		uncle->color = RB_BLACK;
		*pt = grand_parent;
	}
	else
	{
		if (*pt == parent->right)
		{
			btree_rotateleft(root, parent);
			*pt = parent;
			parent = (*pt)->parent;
		}
		btree_rotateright(root, grand_parent);
		btree_swapcolor(parent, grand_parent);
		*pt = parent;
	}
}

static void	btree_parentright(t_btree **root, t_btree **pt, t_btree *parent,
		t_btree *grand_parent)
{
	t_btree	*uncle;

	uncle = grand_parent->left;
	if (uncle && uncle->color == RB_RED)
	{
		grand_parent->color = RB_RED;
		parent->color = RB_BLACK;
		uncle->color = RB_BLACK;
		*pt = grand_parent;
	}
	else
	{
		if (*pt == parent->left)
		{
			btree_rotateright(root, parent);
			*pt = parent;
			parent = (*pt)->parent;
		}
		btree_rotateleft(root, grand_parent);
		btree_swapcolor(parent, grand_parent);
		(*pt) = parent;
	}
}

int			btree_balancefrom(t_btree **root, t_btree *pt)
{
	t_btree	*parent;
	t_btree	*grand_parent;

	while (pt && pt->parent && pt != *root && pt->color != RB_BLACK &&
			pt->parent->color == RB_RED && pt->parent->parent)
	{
		parent = pt->parent;
		grand_parent = parent->parent;
		if (parent == grand_parent->left)
			btree_parentleft(root, &pt, parent, grand_parent);
		else
			btree_parentright(root, &pt, parent, grand_parent);
	}
	(*root)->color = RB_BLACK;
	return (0);
}
