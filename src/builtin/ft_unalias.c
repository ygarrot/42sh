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

void	ft_unalias(char **arg, char ***env)
{
	void	*tmp;
	t_btree **root;
	int		len;

	(void)env;
	root = alias_tb();
	if (!arg)
	{
		ft_printf("alias: An error occured\n");
		return ;
	}
	if (!ft_strcmp(arg[1], "-a"))
		btree_erase(root, erasehash);
	if ((root = btree_search_item(*root, &arg[1], ft_hashcmp)))
		ft_printf("%s\n", ((char**)(*root)->item)[1]);
	(void)tmp;(void)len;
}
