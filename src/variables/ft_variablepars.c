/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variablepars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 13:17:26 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/03 15:44:18 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*ft_variablepars_bracket(char *str)
{
	t_variable	*var;
	size_t		i;
	char		*tmp;

	if (!str || *str != '$' || str[1] != '{')
		return (0);
	i = 2;
	while (str[i] && !ft_isin(str[i], VAR_LIM))
		i += ft_lenchar_r(str, i);
	if (str[i] != '}')
		return (0);
	str[i] = 0;
	var = ft_variableget(&str[2]);
	if (!var)
		tmp = ft_getenv_fromroot(&str[2]);
	str[i] = '}';
	if (!var && !tmp)
		return ((char*)ft_memalloc(1));
	if (!var)
		return ((char*)ft_strdup(tmp));
	tmp = ft_variablestr(*var);
	return (tmp);
}

/*
** Give string beginning with $ to ft_variablepars to get the
** value of the variable
** The string returned can latter be freed with free (2)
** If the variable isn't set, "" is returned (default value)
** If NULL is returned, an error occured
*/

char	*ft_variablepars(char *str)
{
	t_variable	*var;
	size_t		i;
	char		c;
	char		*tmp;

	if (!str || *str != '$')
		return (0);
	if (str[1] == '{')
		return (ft_variablepars_bracket(str));
	i = 1;
	while (str[i] && !ft_isin(str[i], VAR_LIM))
		i += ft_lenchar_r(str, i);
	c = str[i];
	str[i] = 0;
	var = ft_variableget(&str[1]);
	str[i] = c;
	if (!var)
	{
		tmp = ft_getenv_fromroot(&str[1]);
		if (!tmp)
			return ((char*)ft_memalloc(1));
		return (ft_strdup(tmp));
	}
	tmp = ft_variablestr(*var);
	return (tmp);
}

size_t	ft_variablelen(t_variable var)
{
	int			i;
	size_t		len;

	if (var.deep < 1 || var.deep > 2)
		return (0);
	if (var.deep == 1)
		return (ft_strlen(var.str));
	if (!(var.array))
		return (0);
	i = 0;
	len = 0;
	while (var.array[i])
		len += ft_strlen(var.array[i]) + 1;
	if (i > 0)
		len -= 1;
	return (len);
}

char	*ft_variablestr(t_variable var)
{
	char	*value;
	size_t	len;
	int		i;

	if (var.deep < 1 || var.deep > 2)
		return (0);
	if (var.deep == 1)
		return (ft_strdup(var.str));
	if (!(len = ft_variablelen(var)))
		return (ft_strdup(" "));
	if (!(value = (char*)malloc(len)))
		return (0);
	value[0] = 0;
	len = 0;
	i = 0;
	while (var.array[i])
	{
		ft_strcat(&value[len], var.array[i]);
		len += ft_strlen(&value[len]);
		i++;
		if (var.array[i])
			value[len++] = ' ';
	}
	return (value);
}
