/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_assign.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 12:40:00 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/16 12:00:29 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	ft_read_assign__(t_read *parser, char **array, char *tmp_name,
	void *tmp_data)
{
	ft_free_dblechar_tab(array);
	if (parser->error)
	{
		ft_strdel(&tmp_name);
		ft_memdel(&tmp_data);
	}
	return (parser->error ? -1 : 0);
}

static int	ft_read_assign_(t_read *parser, char **array, int i)
{
	char	*tmp_name;
	void	*tmp_data;

	tmp_name = 0;
	tmp_data = 0;
	if (!parser->error && array[i])
	{
		tmp_name = ft_strdup(parser->variables[i]);
		tmp_data = ft_strtbdup(&array[i]);
		parser->error = (!tmp_name || !tmp_data);
		if (!parser->error && ft_variableadd(tmp_name, tmp_data,
			2, ft_variable_isdeported(parser->variables[i])) == -1)
			parser->error = 1;
	}
	while (!parser->error && parser->variables[i] && parser->deep == 1)
	{
		tmp_name = ft_strdup(parser->variables[i]);
		tmp_data = ft_memalloc(1);
		parser->error = (!tmp_name || !tmp_data);
		if (!parser->error && ft_variableadd(tmp_name, tmp_data, 1,
			ft_variable_isdeported(parser->variables[i])) == -1)
			parser->error = 1;
		i++;
	}
	return (ft_read_assign__(parser, array, tmp_name, tmp_data));
}

int			ft_read_assign(t_read *parser, char *str)
{
	char	**array;
	int		i;
	char	*tmp_name;
	void	*tmp_data;

	if (!str || !parser || (i = 0))
		return (-1);
	if (!(array = ft_read_split(parser, str)))
		return (-1);
	while (!parser->error && array[i] && parser->deep == 1 &&
	parser->variables[i] && (parser->variables[i + 1] || !array[i + 1]))
	{
		tmp_name = ft_strdup(parser->variables[i]);
		tmp_data = (void*)ft_strdup(array[i]);
		parser->error = (!tmp_name || !tmp_data);
		if (parser->error || ft_variableadd(tmp_name, tmp_data, 1,
				ft_variable_isdeported(parser->variables[i])) == -1)
			parser->error = 1;
		if (parser->error)
			ft_strdel(&tmp_name);
		if (parser->error)
			ft_memdel(&tmp_data);
		i++;
	}
	return (ft_read_assign_(parser, array, i));
}
