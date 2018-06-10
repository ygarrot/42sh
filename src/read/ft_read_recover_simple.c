/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_recover_simple.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 13:08:28 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/10 13:18:33 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static char	*ft_read_recover_simple_join(char *str, char *buff, int lenbuff)
{
	size_t	i;
	char	*re;
	size_t	j;

	if (!str || !buff || !*buff)
		return (str);
	if (!(re = (char*)malloc(ft_strlen(str) + lenbuff + 1)))
	{
		ft_strdel(&str);
		return (0);
	}
	i = 0;
	j = 0;
	while (str[i])
		re[j++] = str[i++];
	i = 0;
	while (i < lenbuff)
		re[j++] = buff[i++];
	re[j] = 0;
	ft_strdel(&str);
	return (re);
}

char		*ft_read_recover_simple(t_read *parser)
{
	char	*str;
	char	buff[BUFFSIZE + 1];
	int		re;
	int		bl;

	if (!parser || !(str = ft_memalloc(1)))
		return (0);
	re = 1;
	bl = 0;
	while (str && re > 0)
	{
		if ((re = read(parser->fd, buff, BUFFSIZE)) <= 0)
			break ;
		buff[re] = 0;
		re = 0;
		while (buff[re] && (buff[re] != parser->delim || bl))
		{
			re++;
			bl = (buff[re] == '\\' && !bl && parser->bl_active);
		}
		str = ft_read_recover_simple_join(str, buff, re);
		if (buff[re])
			re = -1;
	}
	return (str);
}
