/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 15:22:01 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/17 12:30:57 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_btree		**ft_variable(t_btree **val)
{
	static t_btree	**root = 0;

	if (!root)
		root = val;
	return (root);
}

int			ft_variableadd(char *name, void *data, int deep)
{
	t_variable	*var;
	t_btree		**root;
	t_btree		*pt;

	if (!(var = ft_variable_create(name, data, deep)))
		return (-1);
	if (!(root = ft_variable(0)))
	{
		if (!(pt = btree_create_node((void*)var, RB_BLACK)))
		{
			ft_memdel((void**)&var);
			return (-1);
		}
		ft_variable(&pt);
	}
	else if (btree_insert_data(root, var, &ft_variablecmp))
	{
		ft_memdel((void**)&var);
		return (-1);
	}
	return (0);
}

t_variable	*ft_variableget(char *name)
{
	t_btree		**root;
	void		*var;
	t_variable	v;

	if (!name)
		return (0);
	if (!(root = ft_variable(0)))
		return (0);
	ft_bzero((void*)&v, sizeof(v));
	v.name = name;
	var = btree_search_item(*root, (void*)&v, &ft_variablecmp);
	if (!var || !((t_variable*)var)->name)
		return (0);
	return ((t_variable*)var);
}

size_t		ft_variablelen(char *name)
{
	t_variable	*var;
	int			i;
	size_t		len;

	var = ft_variableget(name);
	if (!var || var->deep < 1 || var->deep > 2)
		return (0);
	if (var->deep == 1)
		return (ft_strlen(var->str));
	if (!(var->array))
		return (0);
	i = 0;
	len = 0;
	while (var->array[i])
		len += ft_strlen(var->array[i]);
	len += (size_t)i;
	if (i > 0)
		len -= 1;
	return (len);
}
