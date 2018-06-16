/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_assign.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 12:40:00 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/16 14:17:39 by tcharrie         ###   ########.fr       */
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
	char	*tmp_name;
	void	*tmp_data;

	tmp_name = 0;
	tmp_data = 0;
	if (!parser->error && parser->deep == 2)
	{
		tmp_name = ft_strdup(parser->variables[i]);
		tmp_data = ft_strtbdup(&array[i]);
		parser->error = (!tmp_name || !tmp_data);
		if (!parser->error && ft_variableadd(tmp_name, tmp_data,
			2, ft_variable_isdeported(parser->variables[i])) == -1)
			parser->error = 1;
		if (parser->error)
			ft_strtbdup(tmp_data);
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
	while (!parser->error && array[i] && parser->deep == 1 &&
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
