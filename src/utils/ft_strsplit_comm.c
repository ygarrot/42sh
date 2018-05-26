/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_comm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 11:27:38 by ygarrot           #+#    #+#             */
/*   Updated: 2018/05/17 14:33:37 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int		countletters(char const *s, char *c)
{
	int		cl;
	int		co;

	cl = 0;
	while (s[cl] && !ft_isin(s[cl], c))
	{
		while ((co = skip_comm((char*)&s[cl])))
			cl += co;
		if (s[cl] && !ft_isin(s[cl], c))
			cl++;
	}
	return (cl);
}

static int		countwords(char const *s, char *c)
{
	int i;
	int i2;

	i = 0;
	i2 = 0;
	while (s[i])
	{
		while (ft_isin(s[i], c) && s[i])
			i++;
		if (s[i] && !ft_isin(s[i], c) && ++i2)
			i += countletters(&s[i], c);
	}
	return (i2);
}

static char		**cpy(char const *s, char *c, char **fresh, int words)
{
	int		i;
	int		i3;
	int		i2;

	i = -1;
	while (++i < words)
	{
		while (*s && ft_isin(*s, c))
			s++;
		i3 = countletters(s, c);
		if (!(fresh[i] = ft_strnew(i3)))
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

char			**ft_strsplit_comm(char *s, char *c)
{
	char	**fresh;
	int		words;

	if (!(s && c))
		return (NULL);
	words = countwords(s, c);
	if (!(fresh = (char**)ft_memalloc((words + 1) * sizeof(char*))))
		return (NULL);
	return (cpy(s, c, fresh, words));
}
