/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 12:38:17 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/08 14:49:18 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_read_parser_select(char c, char *str, t_read *parser)
{
	if (c == 'a')
		return (ft_read_parser_a(parser, str));
	else if (c == 'd')
		return (ft_read_parser_d(parser, str));
	else if (c == 'e')
		return (ft_read_parser_e(parser));
	else if (c == 'i')
		return (ft_read_parser_i(parser, str));
	else if (c == 'n')
		return (ft_read_parser_n(parser, str));
	else if (c == 'N')
		return (ft_read_parser_nn(parser, str));
	else if (c == 'p')
		return (ft_read_parser_p(parser, str));
	else if (c == 'r')
		return (ft_read_parser_r(parser));
	else if (c == 's')
		return (ft_read_parser_s(parser));
	else if (c == 't')
		return (ft_read_parser_t(parser, str));
	else if (c == 'u')
		return (ft_read_parser_u(parser, str));
	else
		return (ft_read_usage(parser));
}

t_read	ft_read_parser(char **arg)
{
	t_read	parser;
	int		i;
	int		j;
	int		k;

	ft_read_initstruct(&parser);
	i = 1;
	while (arg[i] && arg[i][0] == '-' && ft_strcmp(arg[i], "--"))
	{
		k = ft_read_parser_select(arg[i][1], arg[i + 1], &parser);
		j = 2;
		while (k == 1 && arg[i][j])
		{
			k = ft_read_parser_select(arg[i][j], arg[i + 1], &parser);
			j++;
		}
		if (k == -1)
			return (parser);
		i += (k == -1 ? 1 : k);
	}
	i += (arg[i] && !ft_strcmp(arg[i], "--") ? 1 : 0);
	if (parser.deep == 1 && parser.error == 0)
		parser.variables = ft_strtbdup(arg[i] ?
				&arg[i] : (char*[2]){"REPLY", 0});
	return (parser);
}
