/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 12:38:29 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/16 12:44:49 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_read_split_lenword(t_read *parser, char *str)
{
	int		i;
	int		bl;
	char	*delim;

	if (!(delim = ft_read_delim()))
		return (0);
	i = 0;
	bl = 0;
	while (str[i] && (bl || !ft_isin(str[i], delim)))
	{
		bl = (str[i] == '\\' && !bl && parser->bl_active);
		i++;
	}
	return (i);
}

int		ft_read_split_countword(t_read *parser, char *str)
{
	int		i;
	int		bl;
	int		count;
	char	*delim;

	if (!(delim = ft_read_delim()))
		return (0);
	i = 0;
	bl = 0;
	count = 0;
	while (str[i])
	{
		while (!bl && str[i] && ft_isin(str[i], delim))
			i++;
		count++;
		i += ft_read_split_lenword(parser, &str[i]);
	}
	return (count);
}

char	**ft_read_split(t_read *parser, char *str)
{
	char	**array;
	int		i;
	int		count;
	int		len;
	char	*delim;

	if (!(delim = ft_read_delim()))
		return (0);
	count = ft_read_split_countword(parser, str);
	if (!(array = (char**)ft_memalloc((sizeof(char *) * (count + 1)))))
		return (0);
	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && ft_isin(str[i], delim))
			i++;
		len = ft_read_split_lenword(parser, &str[i]);
		array[count] = (str[i] && len) ? (ft_strndup(&str[i], len)) : (0);
		if (str[i] && !array[count] && 0)
		{
			ft_free_dblechar_tab(array);
			return (0);
		}
		count++;
		i += len;
	}
	return (array);
}
