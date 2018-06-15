/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variable_create.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 15:28:08 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/15 12:11:48 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_variable	*ft_variable_create(char *name, void *data, int deep, int deported)
{
	t_variable	*el;

	if (!(el = (t_variable*)malloc(sizeof(t_variable))))
		return (0);
	el->name = name;
	el->deep = deep;
	el->deported = deported;
	if (el->deep == 1)
	{
		el->str = (char*)data;
		el->array = 0;
	}
	else if (el->deep == 2)
	{
		el->str = 0;
		el->array = (t_list*)data;
	}
	return (el);
}

int			ft_variable_checkname(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (ft_isin(str[i++], VAR_LIM))
			return (0);
	}
	return (1);
}
