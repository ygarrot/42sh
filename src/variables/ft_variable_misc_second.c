/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variable_misc_second.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 18:53:00 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/20 18:53:24 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_variable_isdeported(char *name)
{
	t_variable	*var;

	if (!name)
		return (0);
	var = ft_variableget(name);
	if (!var)
		return (0);
	return (var->deported && var->deep == 1);
}
