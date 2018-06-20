/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_custom.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 16:34:09 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/16 18:15:08 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

static int		countletters(char const *s, char **tb, int opt)
{
	int		cl;
	int		co;

	cl = 0;
	while (get_sep((char*)&s[cl], tb) < 0 && s[cl])
	{
		cl += bracket((char*)&s[cl], "()");
		if (opt)
			while ((co = skip_comm((char*)&s[cl])))
				cl += co;
		if (!opt && ft_isin(s[cl], " \n\t"))
			return (cl);
		if (s[cl] && get_sep((char*)&s[cl], tb) < 0)
			cl++;
	}
	return (cl);
}

static int		countwords(char const *s, char **tb, int opt)
{
	int i;
	int i2;
	int tmp;

	i = 0;
	i2 = 0;
	while (s[i])
	{
		while (!opt && s[i] && ft_isin(s[i], " \n\t"))
			i++;
		if (s[i] && get_sep((char*)&s[i], tb) < 0 && ++i2)
			i += countletters(&s[i], tb, opt);
		while (s[i] && (tmp = get_sep((char*)&s[i], tb)) >= 0 && ++i2)
			i += ft_strlen(tb[tmp]);
	}
	return (i2);
}

static char		**cpy(char const *s, char **tb, char **fresh, int *opt)
{
	int		i;
	int		i3;
	int		i2;
	int		tmp;

	i = -1;
	while (++i < opt[0])
	{
		while (!opt[1] && *s && ft_isin(*s, " \n\t"))
			s++;
		i3 =
			(tmp = get_sep((char*)&(*s), tb)) >= 0 ?
			ft_strlen(tb[tmp]) : countletters(s, tb, opt[1]);
		if (i3 && !(fresh[i] = ft_strnew(i3)))
		{
			ft_free_dblechar_tab(fresh);
			return (NULL);
		}
		i2 = i3;
		while (--i3 + 1)
			fresh[i][i3] = s[i3];
		s = &s[i2];
	}
	return (fresh);
}

char			**ft_custom_split(char *s, char **tb, int opt)
{
	char	**fresh;
	int		op[2];

	if (!(s && tb))
		return (NULL);
	op[0] = countwords(s, tb, opt);
	op[1] = opt;
	if (!(fresh = (char**)ft_memalloc((op[0] + 1) * sizeof(char*))))
		return (NULL);
	return (cpy(s, tb, fresh, op));
}
