/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variable_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 12:42:00 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/15 12:11:31 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	ft_variableadd_(t_variable *var, t_btree **root)
{
	t_variable	*prev;

	prev = ft_variableget(var->name);
	if (prev && prev->deep == 2 && var->deep == 2)
	{
		ft_strdel(&(var->name));
		ft_lstfusion(&(prev->array), var->array, &ft_variable_arraycmp);
		free(var);
		var = 0;
	}
	else if (btree_insert_data(root, var, &ft_variablecmp, &ft_variabledel))
	{
		ft_variabledel(var);
		return (-1);
	}
	return (0);
}

int			ft_variableadd(char *name, void *data, int deep, int deported)
{
	t_variable	*var;
	t_btree		**root;

	if (!(root = ft_variable()))
		return (-1);
	if (!(var = ft_variable_create(name, data, deep, deported)))
		return (-1);
	if (!*root)
	{
		if (!(*root = ft_memalloc(sizeof(t_btree))))
		{
			ft_variabledel(var);
			return (-1);
		}
		root[0]->item = var;
		return (root[0] && root[0]->item ? 0 : -1);
	}
	return (ft_variableadd_(var, root));
}
