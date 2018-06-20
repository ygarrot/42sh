/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_recover_misc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 12:33:20 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/20 14:30:32 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_read_recover_sig(char **str, t_read parser)
{
	if (ft_sigint(0) || !str)
	{
		ft_strdel(str);
		return (1);
	}
	if (ft_read_timer_sig_interrup(0))
	{
		ft_addtofd(*str, parser.fd);
		ft_strdel(str);
		return (1);
	}
	return (0);
}

int		ft_read_recover_end(char **str, t_read p)
{
	size_t	size;
	int		bl;

	if ((size = ft_read_recover_sig(str, p)))
		return (size);
	size = ft_strlen(*str);
	if (p.nchars_exact > 0 && size > p.nchars_exact)
		ft_addtofd(&str[0][size + 1], p.fd);
	if (p.nchars_exact > 0)
		return (size >= p.nchars_exact);
	size = 0;
	bl = 0;
	while (str[0][size] && (p.nchars <= 0 || size < p.nchars) && (bl ||
		!p.delim || !ft_strprefix(p.delim, &str[0][size])))
	{
		bl = (p.bl_active && str[0][size] == '\\' && !bl);
		size += ft_lenchar_r(str[0], size);
	}
	if (str[0][size] || (p.nchars > 0 && p.nchars == size))
	{
		str[0][size] = 0;
		ft_addtofd(&str[0][size + 1], p.fd);
		return (1);
	}
	return (0);
}

int		ft_read_recover_init(t_read *parser, int *val, size_t size,
		t_line *line)
{
	if (!parser)
		return (-1);
	ft_bzero((void*)val, size);
	if (!(line->line = (char*)ft_memalloc(ft_strlen(parser->readline) +
					ft_strlen(parser->prompt) + 1)))
		return (-1);
	line->eof = 0;
	line->size_eof = 0;
	line->size_line = 1;
	if (parser->prompt)
		ft_strcat(line->line, parser->prompt);
	if (parser->readline)
		ft_strcat(line->line, parser->readline);
	if (parser->echo)
		ft_putstr_fd(line->line, parser->fd);
	val[1] = ft_strlen(parser->prompt);
	val[5] = val[1];
	val[0] = val[1] + ft_strlen(parser->readline);
	val[4] = 1;
	return (0);
}
