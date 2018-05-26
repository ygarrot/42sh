/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variablepars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 13:17:26 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/12 13:17:27 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*ft_variablepars(char *name, char *pattern)
{
	char		*str;
	t_variable	*var;
	size_t		i;

	if (!(var = ft_variableget(name)))
		return (0);
	if ((var->deep == 1 && !(var->str)) || (var->deep == 2 && !(var->array)))
		return (0);
	if (deep == 1)
		return (ft_strdup(var->str));
	else
	{
		if (!(i = ft_variablelen(name)))
			return (0);
		if (!(str = ft_memalloc(i + 1)))
			return (0);
		i = 0;
		while (var->array[i])
			ft_strcat(str, var->array[i++]);
		return (str);
	}
}
