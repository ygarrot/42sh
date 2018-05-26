/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 14:52:25 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/06 16:26:08 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

/*
** Ajouter len éléments de str au début de src qui est de taille len
** Considère que src est suffisament grand pour l'accueillir
*/

int		ft_insert_noalloc(char *src, char *str, int size)
{
	int	len;

	if (!src || !str)
		return (-1);
	if (size < 1)
		return (1);
	len = ft_strlen(src) + size;
	while (len-- > size)
		src[len] = src[len - size];
	while (size-- > 0)
		src[size] = str[size];
	return (1);
}
