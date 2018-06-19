/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_assign.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 12:40:00 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/19 14:53:46 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	ft_read_assign__(t_read *parser, char **array, char *tmp_name,
	int i)
{
	if (array)
	{
		while (array[i])
			ft_strdel(&array[i++]);
		free(array);
	}
	if (parser->error)
		ft_strdel(&tmp_name);
	return (parser->error ? -1 : 0);
}

static int	ft_read_assign_(t_read *parser, char **array, int i)
{
	char				*tmp_name;
	t_list				*lst;
	t_variable_array	el;

	tmp_name = 0;
	if (!parser->error && parser->deep == 2)
	{
		lst = 0;
		if ((tmp_name = ft_strdup(parser->variables[i])))
		{
			i = 0;
			while (array[i])
			{
				el.str = array[i];
				el.index = i;
				ft_lstpushback(&lst, ft_lstnew((void*)&el, sizeof(el)));
				i++;
			}
		}
		parser->error = (!tmp_name || !lst);
		if (!parser->error && ft_variableadd(tmp_name, lst,
			2, ft_variable_isdeported(parser->variables[0])) == -1)
			parser->error = 1;
	}
	return (ft_read_assign__(parser, array, tmp_name, i));
}

int			ft_read_assign(t_read *parser, char *str)
{
	char	**array;
	int		i;
	char	*tmp_name;

	if (!str || !parser || (i = 0))
		return (-1);
	if (!(array = ft_read_split(parser, str)))
		return (-1);
	while (parser->deep == 1 && !parser->error && array[i] &&
	parser->variables[i] && (parser->variables[i + 1] || !array[i + 1]))
	{
		tmp_name = ft_strdup(parser->variables[i]);
		parser->error = (!tmp_name);
		if (parser->error || ft_variableadd(tmp_name, array[i], 1,
				ft_variable_isdeported(parser->variables[i])) == -1)
			parser->error = 1;
		if (parser->error)
			ft_strdel(&tmp_name);
		i++;
	}
	return (ft_read_assign_(parser, array, i));
}
