/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisin_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/01 12:16:11 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/06 17:21:40 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strisin_tab(char *tofind, char **tab, int option)
{
	int		i;

	i = 0;
	if (!tab || !tofind)
		return (-1);
	if (!option)
	{
		while (tab[i] && ft_strcmp(tofind, tab[i]))
			i++;
		return (tab[i] ? i : -1);
	}
	else
	{
		while (i != option && tab[i] && !ft_strcmp(tofind, tab[i], ft_strlento(tofind, ' '))
			i++;
		return ((i != option) ? i : -1);
	}
}
