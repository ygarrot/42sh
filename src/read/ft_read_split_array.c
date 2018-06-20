/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_split_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:56:12 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/20 18:13:11 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_read_split_countword(t_read *parser, char *str, char *delim)
{
	int	i;
	int	bl;
	int	c;

	i = 0;
	bl = 0;
	c = 0;
	while (str[i])
	{
		while (str[i] && ft_isin_unicode(&str[i], delim))
			i += ft_lenchar_r(str, i);
		if (str[i])
			c++;
		while (str[i] && (bl || !ft_isin_unicode(&str[i], delim)))
		{
			bl = (!bl && parser->bl_active && str[i] == '\\');
			i += ft_lenchar_r(str, i);
		}
	}
	return (c + 1);
}

int		ft_read_split_array_assign(t_read *parser, char *str,
		char **array, char *delim)
{
	int	i;
	int	j;
	int	bl;

	i = 0;
	while (str[i] && ft_isin_unicode(&str[i], delim))
		i += ft_lenchar_r(str, i);
	if (!str[i])
		return (0);
	j = 0;
	while (str[i + j] && (bl || !ft_isin_unicode(&str[i + j], delim)))
	{
		bl = (!bl && parser->bl_active && str[i + j] == '\\');
		j += ft_lenchar_r(str, i + j);
	}
	*array = ft_strndup(&str[i], j);
	return (*array ? i + j : -1);
}

char	**ft_read_split_array(t_read *parser, char *str)
{
	char	**array;
	int		i;
	int		j;
	int		count;
	char	*delim;

	if (!str || !parser || (i = 0))
		return (0);
	if (!(delim = ft_read_delim()))
		return (0);
	if (!(array = (char**)ft_memalloc(sizeof(char*) *
					ft_read_split_countword(parser, str, delim))))
		return (0);
	count = 0;
	while ((j = ft_read_split_array_assign(parser,
					&str[i], &array[count++], delim)) > 0)
		i += j;
	*array = (*array == 0 && j >= 0 ? ft_strdup("") : *array);
	if (!*array || j == -1)
	{
		ft_free_dblechar_tab(array);
		return (0);
	}
	return (array);
}
