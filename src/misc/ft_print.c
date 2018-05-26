/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 12:48:50 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/17 10:54:23 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*ft_init_aff(int *val)
{
	char	*local;
	char	*tmp;
	size_t	i;

	if (!(local = (char*)ft_memalloc(100 + 1)))
		return (0);
	if (!(tmp = getcwd(0, 0)))
		ft_strcat(local, "$>");
	else if ((i = ft_strlen(tmp)) || 1)
	{
		while (i && tmp[i] != '/')
			i--;
		i += (tmp[i] == '/');
		ft_strcat(local, &tmp[i]);
		if (!tmp[i])
			ft_strcat(local, "/");
		ft_strcat(local, " >");
		ft_strdel(&tmp);
	}
	ft_putstr(local);
	i = ft_strlen(local);
	val[0] = i;
	val[1] = i;
	val[5] = i;
	return (local);
}

int		writechar(int c)
{
	return (write(STDOUT_FILENO, &c, 1));
}
