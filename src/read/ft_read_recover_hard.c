/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_recover_hard.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 13:08:35 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/10 14:19:29 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*ft_read_recover_hard(t_read *parser)
{
	t_line	line;
	int		val[13];

	if (!parser)
		return (0);
	ft_bzero((void*)&line, sizeof(line));
	ft_bzero((void*)val, sizeof(val));
	if (!(line.line = ft_strdup((parser->prompt) ? (parser->prompt) : "")))
		return (0);
	val[4] = 1;
	val[1] = (int)ft_strlen(parser->prompt);
	if (val[1] <= 0)
		return (line.line);
	line.eof = ft_strdup(&line.line[val[1]]);
	ft_strdel(&line.line);
	return (line.eof);
}
