/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_completion_start.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 14:43:37 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/21 16:08:10 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char		*ft_completion_start(t_line *line, int *val)
{
	char	*str;
	int		i;
	char	*tmp;

	if (!line || !(tmp = val[4] ? line->line : line->eof) || !val)
		return (0);
	if (val[0] <= val[5])
		return (0);
	i = ft_completion_startpos(tmp, val[0]);
	if (i == 0)
		return (0);
	if (!(str = (char*)ft_memalloc(i + 1)))
		return (0);
	val[9] = 0;
	while (i > 0)
		str[val[9]++] = tmp[val[0] - i--];
	return (str);
}
