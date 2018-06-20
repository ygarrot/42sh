/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variable_misc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 11:48:51 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/20 18:53:22 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_variablecmp(void *left, void *right)
{
	if (!left || !right)
		return (0);
	return (ft_strcmp(((t_variable*)left)->name, ((t_variable*)right)->name));
}

void	ft_variable_lstdel(void *content, size_t size)
{
	(void)size;
	if (content)
	{
		ft_strdel(&(((t_variable_array*)content)->str));
		free(content);
	}
}

void	ft_variabledel_tree(void *content)
{
	t_variable	*v;

	if (!content)
		return ;
	v = (t_variable*)content;
	ft_strdel(&(v->name));
	ft_strdel(&(v->str));
	ft_lstdel(&(v->array), &ft_variable_lstdel);
	free(v);
	v = 0;
}

void	ft_variabledel(void *content, size_t size)
{
	t_variable	*v;

	if (!content || size == 0)
		return ;
	v = (t_variable*)content;
	ft_strdel(&(v->name));
	ft_strdel(&(v->str));
	ft_lstdel(&(v->array), &ft_variable_lstdel);
	free(v);
	v = 0;
}

int		ft_variable_arraycmp(void *left, void *right)
{
	if (!right || !left)
		return (0);
	if (((t_variable_array*)left)->index < ((t_variable_array*)right)->index)
		return (-1);
	if (((t_variable_array*)left)->index == ((t_variable_array*)right)->index)
		return (0);
	return (1);
}
