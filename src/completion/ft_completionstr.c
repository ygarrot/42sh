/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_completionstr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 15:18:16 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/21 16:00:00 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	ft_straddsep_(char *str, char *split, int sep, int *i)
{
	while (sep && str[i[0]])
	{
		if (str[i[0]] == '\\' && sep != '\'')
		{
			split[i[1]++] = '\\';
			split[i[1]++] = '\\';
		}
		if (str[i[0]] == sep && sep == '\'')
		{
			split[i[1]++] = sep;
			split[i[1]++] = '\\';
			split[i[1]++] = sep;
			sep = 0;
		}
		else if (str[i[0]] == sep)
		{
			split[i[1]++] = '\\';
			split[i[1]++] = sep;
		}
		else
			split[i[1]++] = str[i[0]];
		i[0]++;
	}
}

char		*ft_straddsep(char *str, int bl, int sep)
{
	char	*split;
	int		i[2];

	if (!str)
		return (0);
	if (!(split = (char*)ft_memalloc(2 * ft_strlen(str) + 3)))
		return (0);
	ft_bzero((void*)i, sizeof(i));
	if (bl)
		split[i[1]++] = str[i[0]++];
	ft_straddsep_(str, split, sep, i);
	while (str[i[0]])
	{
		if (ft_isin(str[i[0]], SPECIALCHAR))
			split[i[1]++] = '\\';
		split[i[1]++] = str[i[0]++];
	}
	return (split);
}

char		*ft_strpurgesep(char *str)
{
	int		i;
	char	*purged;
	int		j;
	int		sep[3];

	if (!str)
		return (0);
	if (!(purged = (char*)ft_memalloc(ft_strlen(str) + 1)))
		return (0);
	i = 0;
	j = 0;
	ft_bzero((void*)sep, sizeof(sep));
	while (str[i])
	{
		ft_separator(str[i], &sep[1], &sep[2], 0);
		if (sep[1] != sep[0] || sep[2])
			i++;
		else
			purged[j++] = str[i++];
		sep[0] = sep[1];
	}
	return (purged);
}
