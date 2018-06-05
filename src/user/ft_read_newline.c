/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_newline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 11:48:59 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/27 14:15:31 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

void	ft_newline_active_(char c, int *sep)
{
	if (!sep[2] && c == '`' && sep[0] != '\'' && !sep[1])
	{
		sep[2] = '`';
		sep[3] = '`';
	}
	else if (sep[2] && c == '`' && !sep[1] && sep[2] == sep[3])
	{
		sep[2] = 0;
		sep[3] = sep[0];
	}
}

int		ft_newline_active(char *str)
{
	int	sep[4];
	int	i;

	i = 0;
	ft_bzero((void*)sep, sizeof(sep));
	while (str[i] && str[i + 1])
	{
		if (!sep[0] && !sep[1] && ft_isin(str[i], "'\""))
		{
			sep[0] = str[i];
			sep[3] = sep[0];
		}
		else if (sep[0] == str[i] && !sep[1] && sep[0] == sep[3])
		{
			sep[0] = 0;
			sep[3] = sep[2];
		}
		else
			ft_newline_active_(str[i], sep);
		sep[1] = (!sep[1] && str[i] == '\\' && sep[0] != '\'');
		i++;
	}
	return (!(sep[0] || sep[1] || sep[2]));
}

int		ft_read_newline(t_line *line, int *val, t_parser *pars)
{
	t_parser	*tmp;

	ft_printchar(line, "\n", val);
	if (val[4])
	{
		if (!ft_newline_active(&(line->line)[val[1]]))
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
		pars->drop = 1;
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
	else if (val[0] == val[5] && val[4] == 0)
	{
		if (!parser)
			return (-1);
		line->parser_nb++;
		parser->drop = 2;
		if (ft_printchar(line, "\n", val) < 0)
		{
			ft_errorlog("Failed to print");
			return (-1);
		}
		val[9] = (parser->next == 0 && parser->wait == 0);
		line->eof[val[0]++] = 0;
		val[5] = val[0];
		val[3] = val[0];
		val[4] = (parser->next == 0);
		return (val[9]);
	}
	return (0);
}
