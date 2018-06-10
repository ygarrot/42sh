/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 15:22:01 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/06 12:41:07 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_btree		**ft_variable(void)
{
	static t_btree	**root = 0;

	if (!root)
		root = ft_memalloc(sizeof(t_btree*));
	if (!root)
		return (0);
	return (root);
}

t_variable	*ft_variableget(char *name)
{
	t_btree		**root;
	void		*var;
	t_variable	v;

	if (!name)
		return (0);
	if (!(root = ft_variable()))
		return (0);
	ft_bzero((void*)&v, sizeof(v));
	v.name = name;
	var = btree_search_item(*root, (void*)&v, &ft_variablecmp);
	if (!var)
		return (0);
	return ((t_variable*)var);
}
