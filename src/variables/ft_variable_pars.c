/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variable_pars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 12:42:13 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/20 14:31:00 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_variablepars_bracket_pos(char *str, size_t *i)
{
	int	pos;

	if (!str || !i)
		return (-1);
	pos = 0;
	if (str[*i] != '[')
		return (0);
	i[0]++;
	if (str[*i] < '0' || str[*i] > '9')
		return (-1);
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		pos = pos * 10 + str[*i] - '0';
		i[0]++;
	}
	if (str[*i] == ']')
		i[0]++;
	else
		return (-1);
	return (pos);
}

char	*ft_variablepars_bracket(char *str)
{
	t_variable	*var;
	size_t		i;
	char		*tmp;
	int			pos;

	if (!str || *str != '{')
		return (0);
	i = 1;
	while (str[i] && !ft_isin(str[i], VAR_LIM))
		i += ft_lenchar_r(str, i);
	pos = str[i];
	str[i] = 0;
	var = ft_variableget(&str[1]);
	str[i] = pos;
	pos = ft_variablepars_bracket_pos(str, &i);
	printf("%d\n", pos);
	if (str[i] != '}' || pos == -1)
		return (0);
	if (!var)
		tmp = ft_getenv_fromroot(&str[1]);
	if (!var && !tmp)
		return ((char*)ft_memalloc(1));
	if (!var)
		return ((char*)ft_strdup(tmp));
	return (ft_variablestr(*var, pos));
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

	if (!str || (ft_isin(*str, VAR_LIM) && *str != '{'))
		return (0);
	if (*str == '{')
		return (ft_variablepars_bracket(str));
	i = 0;
	while (str[i] && !ft_isin(str[i], VAR_LIM))
		i += ft_lenchar_r(str, i);
	c = str[i];
	str[i] = 0;
	var = ft_variableget(str);
	if (!var)
	{
		tmp = ft_strdup(ft_getenv_fromroot(str));
		if (!tmp)
			tmp = (char*)ft_memalloc(1);
	}
	else
		tmp = ft_variablestr(*var, 0);
	str[i] = c;
	return (tmp);
}

char	*ft_variablestr(t_variable var, int pos)
{
	t_list	*array;

	if (var.deep < 1 || var.deep > 2)
		return (0);
	if (var.deep == 1 && pos == 0)
		return (ft_strdup(var.str));
	else if (var.deep == 1)
		return ((char*)ft_memalloc(1));
	array = var.array;
	while (array && array->content &&
			((t_variable_array*)array->content)->index < pos)
		array = array->next;
	if (array && array->content &&
			((t_variable_array*)array->content)->index == pos)
		return (ft_strdup(((t_variable_array*)array->content)->str));
	else
		return ((char*)ft_memalloc(1));
}
