/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_custom.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 16:34:09 by ygarrot           #+#    #+#             */
/*   Updated: 2018/05/18 16:00:22 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/sh.h"

static int		countletters(char const *s, char **tb)
{
	int		cl;

	cl = 0;
	while (get_sep((char*)&s[cl], tb) < 0  && s[cl])
	{
		if (ft_isin(s[cl], " \n\t"))
			return(cl);
		if (s[cl] && get_sep((char*)&s[cl], tb) < 0)
			cl++;
	}
	return (cl);
}

static int		countwords(char const *s, char **tb)
{
	int i;
	int i2;
	int tmp;

	i = 0;
	i2 = 0;
	while (s[i])
	{
		while (s[i] && ft_isin(s[i], " \n\t"))
			i++;
		while (s[i] && (tmp = get_sep((char*)&s[i], tb)) >= 0 && ++i2)
			i += ft_strlen(tb[tmp]);
		if (s[i] && get_sep((char*)&s[i], tb) < 0 && ++i2)
			i += countletters(&s[i], tb);
	}
	return (i2);
}

static char		**cpy(char const *s, char **tb, char **fresh, int words)
{
	int		i;
	int		i3;
	int		i2;
	int		tmp;

	i = -1;
	while (++i < words)
	{
		while (*s && ft_isin(*s, " \n\t"))
			s++;
		i3 = (tmp = get_sep((char*)&(*s), tb)) >= 0 ?
			ft_strlen(tb[tmp]) : countletters(s, tb);
		if (i3 && !(fresh[i] = ft_strnew(i3)))
		{
			ft_free_dblechar_tab(fresh);
			return (NULL);
		}
		i2 = i3;
		while (--i3 + 1)
		{
			fresh[i][i3] = s[i3];
		}
		s = &s[i2];
	}
	return (fresh);
}

char			**ft_custom_split(char *s, char **tb)
{
	char	**fresh;
	int		words;

	if (!(s && tb))
		return (NULL);
	words = countwords(s, tb);
	if (!(fresh = (char**)ft_memalloc((words + 1) * sizeof(char*))))
		return (NULL);
	return (cpy(s, tb, fresh, words));
}
