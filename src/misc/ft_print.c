/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 12:48:50 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/03 16:53:05 by tcharrie         ###   ########.fr       */
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

size_t	ft_strlen_vis(char *str)
{
	size_t	i;
	size_t	j;

	if (!str ||! !*str)
		return (0);
	i = 0;
	j = 0;
	while (str[j])
	{
		i++;
		j += ft_lenchar_r(str, j);
	}
	return (i);
}
