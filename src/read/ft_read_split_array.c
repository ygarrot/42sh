/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_split_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 13:14:00 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/19 14:53:12 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_read_split_count(char *str, char *delim)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		while (str[i] && ft_isin_unicode(&str[i], delim))
			i += ft_lenchar_r(str, i);
		if (str[i])
			c++;
		while (str[i] && !ft_isin_unicode(&str[i], delim))
			i += ft_lenchar_r(str, i);
	}
	return (c + 1);
}

int		ft_read_split_len(char *str, char *delim)
{
	int	i;

	if (!str || !delim)
		return (0);
	i = 0;
	while (str[i] && !ft_isin_unicode(&str[i], delim))
		i += ft_lenchar_r(str, i);
	return (i);
}

int		ft_read_split_array_assign(char *str, char *delim, char **array,
		int count)
{
	int	i;
	int	j;

	j = 0;
	while (str[j] && ft_isin_unicode(&str[j], delim))
		j += ft_lenchar_r(str, j);
	i = ft_read_split_len(&str[j], delim);
	if (i <= 0 && count == 0)
		array[0] = ft_strdup("");
	if (i <= 0)
		return (j);
	array[count] = ft_strndup(&str[j], i);
	if (!array[count])
	{
		ft_free_dblechar_tab(array);
		return (-1);
	}
	return (j + i);
}

char	**ft_read_split_array(t_read *parser, char *str)
{
	char	**array;
	int		count;
	int		i;
	char	*delim;
	int		j;

	if (!parser || !str || !parser->variables || !(delim = ft_read_delim()))
		return (0);
	i = 0;
	count = 0;
	if (!(array = ft_memalloc(sizeof(char*) *
			ft_read_split_count(str, delim))))
		return (0);
	while ((j = ft_read_split_array_assign(&str[i], delim, array, count)) > 0)
	{
		i += j;
		count++;
	}
	return (j >= 0 ? array : 0);
}
