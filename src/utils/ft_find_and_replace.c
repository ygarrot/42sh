/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_and_replace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 11:55:23 by ygarrot           #+#    #+#             */
/*   Updated: 2018/05/27 15:39:33 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

/*
** Cherche un charactere dans une chaine et le remplace par un autre charactere
** Sauf si celui-ci n'existe pas, dans ces cas la le char sera vide;
** op : 1 pour skip les comments
*/

int			skip_co(char *str)
{
	int		i;
	char	q;

	q = 0;
	i = 0;
	if (!str || !*str)
		return (0);
	while (ft_isin(str[i], QUOTES) && (q = str[i++]))
	{
		if (ft_charchr(q, &str[i]) < 0)
			return (0);
		while (str[i] && str[i] != q)
		{
			i += str[i + 1] && str[i] == '\\' ? 2 : 1;
			if (!str[i])
				return (0);
		}
	}
	return (i);
}

static char	*replace(char *str, char *rep, int op, int len)
{
	char	*ret;
	char	q;
	int		i;
	int		i2;

	i = 0;
	i2 = -1;
	mallcheck((ret = ft_strnew(len)));
	while (str[i] && !(q = 0))
	{
		while (op & 1 && ft_isin(str[i], QUOTES)
			&& (ft_charchr(str[i], &str[i + 1]) >= 0) && (q = str[i]))
		{
			while (str[++i] && str[i] != q &&
			(((q == '\"' && str[i] == '\\') ? ++i : 0) || 1))
				ret[++i2] = str[i];
		}
		while (str[i] == '\\' && str[i + 1] && ++i)
			ret[++i2] = str[i++];
		if (str[i] && (q == str[i] || str[i] == rep[0]) && ++i)
			rep[1] ? ret[++i2] = rep[1] : 0;
		else if (str[i])
			ret[++i2] = str[i++];
	}
	return (ret);
}

char		*ft_find_and_replace(char *str, char *rep, int op)
{
	int		len;
	int		i;
	int		temp;

	i = 0;
	temp = 0;
	len = ft_strlen(str);
	if (!str)
		return (NULL);
	while (str[i])
	{
		while (str[i] == '\\' && len--)
			i += str[i + 1] ? 2 : 1;
		while (op & 1 && (temp = skip_co(&str[i])))
		{
			i += temp;
			temp ? len -= 2 : 0;
		}
		!rep[1] && str[i] && str[i++] == rep[0] ? len-- : 0;
	}
	return (replace(str, rep, op, len));
}
