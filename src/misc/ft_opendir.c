/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opendir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 11:09:49 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/21 11:09:50 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

DIR	*ft_opendirfree(char *str)
{
	DIR	*dir;

	if (!str)
		return (0);
	dir = opendir(str);
	ft_strdel(&str);
	return (dir);
}
