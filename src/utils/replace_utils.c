/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 12:10:51 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/17 14:46:55 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

int		skip_double(char *str)
{
	int		i;
	char	q;

	i = 0;
	if (!str || !*str)
		return (0);
	if (str[i] == '\'' && (q = str[i++]))
	{
		while (str[i] && str[i++] != q)
			if (!str[i])
				return (0);
	}
	if (str[i] == '\\')
		i += str[i + 1] ? 2 : 1;
	return (i);
}

int		local_env(char **tmp, char *todel)
{
	int ret;

	ret = 0;
	*tmp = ft_variablepars(todel);
	ft_memdel((void**)&todel);
	return (2);
}
