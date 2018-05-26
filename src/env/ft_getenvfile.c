/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenvfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 13:03:01 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/15 18:33:58 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*ft_getenvfile(int code)
{
	static char		*str = 0;
	char			*tmp;

	if (!ENVFILE)
		return (0);
	if (!str)
		str = ft_strdup(ENVFILE);
	if (code == CODE_ENVADD)
	{
		if (!(tmp = (char*)ft_memalloc(ft_strlen(str) + 2)))
			return (0);
		ft_strcat(tmp, str);
		tmp[ft_strlen(str)] = '0';
		ft_cpy(str, tmp);
		ft_strdel(&str);
		str = tmp;
	}
	else if (code == CODE_ENVGET)
		return (ft_strdup(str));
	return (0);
}
