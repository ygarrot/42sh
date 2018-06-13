/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_recover.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 12:18:57 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/13 14:09:40 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_read_recover_end(char *str, t_read p)
{
	size_t	size;

	size = ft_strlen(str);
	if (ft_read_timer_sig_interrup(0) == 1)
		return (1);
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

char	*ft_read_recover(t_read *parser)
{
	char	*str;
	int		val[14];

	if (!parser)
		return (0);
	ft_bzero((void*)val, sizeof(val));
	while (str && ft_read_recover_end(str, *p))
	{
	}
	return (str);
}
