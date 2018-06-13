/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_parser_assign.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 12:38:20 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/13 11:48:32 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int	ft_read_parser_a(t_read *parser, char *str)
{
	if (!str)
		return (ft_read_usage(parser));
	if (!parser)
		return (2);
	parser->deep = 2;
	if (!(str = ft_strdup(str)))
	{
		ft_putstr_fd("21sh: read: Failed to malloc\n", STDERR_FILENO);
		parser->error = 1;
		return (-1);
	}
	parser->variables = ft_strtbdup((char*[2]){str, 0});
	if (!(parser->variables))
	{
		ft_strdel(&str);
		ft_putstr_fd("21sh: read: Failed to malloc\n", STDERR_FILENO);
		parser->error = 1;
		return (-1);
	}
	return (2);
}

int	ft_read_parser_d(t_read *parser, char *str)
{
	if (!str)
		return (ft_read_usage(parser));
	if (!parser)
		return (2);
	ft_strdel(&parser->delim);
	parser->delim = ft_strndup(str, ft_lenchar_r(str, 0));
	if (!parser->delim)
	{
		parser->error = 1;
		ft_putstr_fd("21sh: read: An internal error occured\n", STDERR_FILENO);
		return (-1);
	}
	return (2);
}

int	ft_read_parser_e(t_read *parser)
{
	if (!parser)
		return (1);
	parser->readline_active = 1;
	return (1);
}

int	ft_read_parser_i(t_read *parser, char *str)
{
	if (!str)
		return (ft_read_usage(parser));
	if (!parser)
		return (2);
	parser->readline = ft_strdup(str);
	if (!parser->readline)
	{
		parser->error = 1;
		return (-1);
	}
	return (2);
}

int	ft_read_parser_n(t_read *parser, char *str)
{
	int	i;

	if (!str)
		return (ft_read_usage(parser));
	if (!parser)
		return (2);
	i = 0;
	parser->nchars = 0;
	while (str[i] >= '0' && str[i] <= '9')
		parser->nchars = (parser->nchars * 10) + str[i++] - '0';
	if (str[i])
	{
		parser->error = 1;
		ft_putstr_fd("21sh: read: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": invalid number", STDERR_FILENO);
		return (-1);
	}
	return (2);
}
