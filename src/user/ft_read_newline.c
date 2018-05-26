/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_newline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 11:48:59 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/21 11:07:18 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

int		ft_read_newline(t_line *line, int *val, t_parser *pars)
{
	t_parser	*tmp;

	ft_printchar(line, "\n", val);
	if (val[4])
	{
		val[12] = ft_separator_active(line->line, val[0] - 1,
				&val[10], &val[11]);
		if (val[10] || val[11] || val[12])
			return (0);
		if (!(tmp = count_parser(&(line->line)[val[5]])))
			return (-1);
		line->parser_nb++;
		ft_parserpushback(line->parser, tmp);
		if (!line->parser)
			line->parser = tmp;
		if (tmp->comm)
			val[4] = 0;
		if (tmp->comm)
			val[0] = val[3];
		if (tmp->comm || tmp->wait)
			val[5] = val[0];
		return ((tmp->comm || tmp->wait) ? 0 : 1);
	}
	else
		return (ft_read_newline_eof(line, val, pars));
}

int		ft_read_newline_eof(t_line *line, int *val, t_parser *pars)
{
	if (!pars || !line || !line->line || !line->eof)
		return (-1);
	val[9] = 0;
	if ((ft_strlen(pars->comm) == 0 && ft_strlen(&(line->eof)[val[5]])) == 1
	|| (!ft_strncmp(&(line->eof)[val[5]], pars->comm, ft_strlen(pars->comm)) &&
		line->eof[val[5] + (int)ft_strlen(pars->comm)] == '\n'))
	{
		val[9] = (pars->next == 0 && pars->wait == 0);
		line->parser_nb++;
		line->eof[val[0]] = 0;
		val[0]++;
		val[4] = (pars->next == 0);
	}
	val[3] = val[0];
	val[5] = (val[4] ? (int)ft_strlen(line->line) : val[0]);
	val[0] = (val[4] ? val[5] : val[0]);
	return (val[9]);
}

int		ft_read_eot(t_line *line, int *val, t_parser *parser)
{
	if (!line || !val || !line->line || !line->eof)
		return (-1);
	if ((val[4] ? line->line : line->eof)[val[0]])
		return (ft_delete(line, val) == -1 ? -1 : 0);
	if (val[0] == val[1] && val[4])
		ft_exit(0);
	else if (val[0] == val[5])
	{
		if (!parser)
			return (-1);
		val[9] = (parser->next == 0 && parser->wait == 0);
		line->parser_nb++;
		ft_strdel(&(parser->comm));
		if (ft_printchar(line, "\n", val) < 0)
			return (-1);
		line->eof[val[0]] = 0;
		val[0]++;
		val[5] = val[0];
		val[3] = val[0];
		val[4] = (parser->next == 0);
		return (val[9]);
	}
	return (0);
}
