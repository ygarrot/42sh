/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 15:52:44 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/15 17:20:00 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_dprintf_basique(fd, str, i)
{
	int	j;

	j = 0;
	while (str[i + j] && str[i + j] != '{' && str[i + j] != '%')
		j++;
	write(fd, &str[i], j);
	return (j);
}

int		ft_dprintf_color(fd, str, i)
{
	int	j;

	if (!str || str[i] != '{')
		return (0);
	if (!ft_strncmp("{whiteblack}", str, 12))
		write(fd, "\33[40;37m", 8);
	else if (!ft_strncmp("{blackwhite}", str, 12))
		write(fd, "\33[47;30m", 8);
	else
	{
		write(fd, "{", 1);
		return (1);
	}
	return (12);
}

int		ft_dprintf(int fd, const char *str, ...)
{
	va_list	list;
	int		i;

	if (!str)
		return (0);
	va_start(list, &fd);
	i = 0;
	while (str[i])
	{
		i += ft_dprintf_basique(fd, str, i);
		i += ft_dprintf_color(fd, str, i);
		i += ft_dprintf_list(fd, str, i, list);
	}
	va_end(list);
	return (i);
}
