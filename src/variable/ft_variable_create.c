/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variable_create.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 15:28:08 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/17 12:47:34 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_variable	*ft_variable_create(char *name, void *data, int deep)
{
	t_variable	*el;

	if (!(el = (t_variable*)malloc(sizeof(t_variable))))
		return (0);
	el->name = name;
	el->deep = deep;
	if (el->deep == 1)
	{
		el->str = (char*)data;
		el->array = 0;
	}
	else if (el->deep == 2)
	{
		el->str = 0;
		el->array = (char**)data;
	}
	return (el);
}
