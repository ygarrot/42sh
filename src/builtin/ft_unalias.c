/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unalias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:37:28 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/09 17:26:29 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/sh.h"

void	erase_alias(void *item)
{
	char	**t;

	t = (char**)item;
	if (!t)
		return ;
	ft_memdel((void**)&t[0]);
	ft_memdel((void**)&t[1]);
	ft_memdel((void**)&t);
}

void	ft_unalias(char **arg, char ***env)
{
	t_btree **root;

	(void)env;
	root = alias_tb();
	if (!arg)
	{
		ft_printf("alias: An error occured\n");
		return ;
	}
	if (!ft_strcmp(arg[1], "-a"))
		btree_erase(root, erasehash);
	else
		btree_remove_data(root, arg, ft_hashcmp, erase_alias);
}
