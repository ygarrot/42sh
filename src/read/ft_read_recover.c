/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_recover.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 12:18:57 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/10 12:26:37 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_read_recover_end(char *str, int pos, t_read *parser)
{
	int	i;
	int	bl;

	if (!str || !parser)
		return (1);
	i = 0;
	bl = 0;
	while (str[i])
	{
		if (!bl && str[i] == parser->delim)
			return (1);
		bl = (parser->bl_active && str[i] == '\\' && !bl);
		i += ft_lenchar_r(str, i);
	}
	return (0);
}

char	*ft_read_recover(t_read *parser)
{
	if (!parser)
		return (0);
	return (0);
}
