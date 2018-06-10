/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_parser_assignn.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 12:38:23 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/08 14:45:32 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int	ft_read_parser_nn(t_read *parser, char *str)
{
	int	i;

	if (!str)
		return (ft_read_usage(parser));
	if (!parser)
		return (2);
	i = 0;
	parser->nchars_exact = 0;
	while (str[i] >= '0' && str[i] <= '9')
		parser->nchars_exact = (parser->nchars_exact * 10) + str[i++] - '0';
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

int	ft_read_parser_p(t_read *parser, char *str)
{
	if (!str)
		return (ft_read_usage(parser));
	if (!parser)
		return (2);
	parser->prompt = ft_strdup(str);
	if (!parser->prompt)
	{
		parser->error = 1;
		ft_putstr_fd("21sh: read: Failed to malloc\n", 2);
		return (-1);
	}
	return (2);
}

int	ft_read_parser_r(t_read *parser)
{
	if (parser)
		parser->bl_active = 0;
	return (1);
}

int	ft_read_parser_s(t_read *parser)
{
	if (parser)
		parser->echo = 0;
	return (1);
}
