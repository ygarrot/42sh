/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 13:28:44 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/20 18:11:17 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

void	epur_tb(t_com *com, int len)
{
	int		i;
	t_paths	*tmp;
	t_tb	*to_del;
	t_tb	*list;

	i = -1;
	if (len <= 0 || !(list = com->tb))
		return ;
	ft_memdel((void**)&com->cli);
	mallcheck(com->cli = (char**)ft_memalloc((len + 1) * sizeof(char*)));
	while (list && (com->len = -1))
	{
		if (list->str)
			com->cli[++i] = list->str;
		else if ((tmp = list->glob->paths))
			while (tmp)
			{
				com->cli[++i] = tmp->path;
				tmp = tmp->next;
			}
		to_del = list;
		list = list->next;
		free_globs(to_del->glob);
		ft_memdel((void**)&to_del);
	}
}

void	erase_shell(t_shell *sh)
{
	t_btree **root;

	if (!sh)
		return ;
	root = alias_tb();
	free_comm(sh);
	ft_free_dblechar_tab(sh->tb_built);
	if (sh->hash_tb)
		erase_hash_tab(sh->hash_tb);
	btree_erase(root, erasehash);
}
