/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 15:52:44 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/15 15:59:46 by tcharrie         ###   ########.fr       */
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
