/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_getline_simple.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 12:13:50 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/10 12:31:35 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*ft_read_recover_simple(t_read *parser)
{
	char	*str;
	char	buff[BUFFSIZE + 1];
	int		re;

	if (!(str = ft_memalloc(1)) || !parser)
		return (0);
	re = 1;
	while (re > 0)
	{
		re = read(parser->fd, buff, BUFFSIZE);
		if (re <= 0)
			break ;
		buff[re] = 0;
		re = 0;
		while (buff[re] && 

	}
	return (str);
}
