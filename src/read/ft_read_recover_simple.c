/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_recover_simple.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 13:08:28 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/13 12:36:18 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	ft_read_simple_end(char *str, t_read p, int pos)
{
	size_t	size;

	size = ft_strlen(str);
	if (p.nchars_exact > 0 && size > p.nchars_exact)
		ft_addtofd(&str[size + 1], p.fd);
	if (p.nchars_exact > 0)
		return (size >= p.nchars_exact);
	if (p.nchars > 0 && size > p.nchars)
		ft_addtofd(&str[size + 1], p.fd);
	if (p.nchars > 0 && size >= p.nchars)
		return (1);
	if (size == 0)
		return (0);
	size = 0;
	while (str[size])
	{
		if (ft_strprefix(p.delim, &str[size]))
			return (1);
		size++;
	}
	return (0);
}

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
	int		pos;

	if (!parser || !(str = ft_memalloc(1)))
		return (0);
	pos = 0;
	re = 1;
	bl = 0;
	while (str && !ft_read_simple_end(str, *parser, pos))
	{
		if ((re = read(parser->fd, buff, BUFFSIZE)) <= 0)
			break ;
		buff[re] = 0;
		pos += re;
		re = 0;
		str = ft_read_recover_simple_join(str, buff, ft_strlen(buff));
	}
	return (str);
}

int	main(int ac, char **av)
{
	t_read	p;
	char	*str;

	ft_read_initstruct(&p);
	p.delim = "O";
	str = ft_read_recover_simple(&p);
	printf("\n{%s}\n", str);
	return (0);
}
