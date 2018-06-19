/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 12:38:29 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/19 13:10:54 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_read_split_lenword(t_read *parser, char *str, char *delim)
{
	int		i;
	int		bl;

	i = 0;
	bl = 0;
	while (str[i] && (bl || !ft_isin(str[i], delim)))
	{
		bl = (str[i] == '\\' && !bl && parser->bl_active);
		i++;
	}
	return (i);
}

char	**ft_read_split_init(t_read *parser, char **delim, char *str)
{
	if (!parser || !parser->variables || !parser->variables[0]
			|| !delim || !str)
		return (0);
	if (!(*delim = ft_read_delim()))
		return (0);
	return ((char**)ft_memalloc((sizeof(char*)) *
				(ft_tablen(parser->variables) + 1)));
}

int		ft_read_split_assign(int yall, char **array, char *str, char *delim)
{
	int	i;
	int	len;

	i = 0;
	while (str[i] && ft_isin(str[i], delim))
		i++;
	len = 0;
	while (str[i + len] && (yall || !ft_isin(str[i + len], delim)))
		len++;
	while (yall && len > 0 && ft_isin(str[i + len], delim))
		len--;
	*array = (str[i] && len > 0) ? (ft_strndup(&str[i], len)) : (0);
	while (yall && str[i + len])
		len++;
	while (str[i + len] && ft_isin(str[i + len], delim))
		len++;
	return (i + len);
}

char	**ft_read_split(t_read *parser, char *str)
{
	char	**array;
	int		i;
	int		count;
	char	*delim;

	if (parser->deep != 1)
		return (parser->deep == 2 ? ft_read_split_array(parser, str) : 0);
	if (!(array = ft_read_split_init(parser, &delim, str)))
		return (0);
	i = 0;
	count = 0;
	while (str[i])
	{
		i += ft_read_split_assign(!(parser->variables[count + 1]),
				&array[count], &str[i], delim);
		if (str[i] && !array[count])
		{
			ft_free_dblechar_tab(array);
			return (0);
		}
		count++;
	}
	while (parser->variables[count])
		array[count++] = (char*)ft_memalloc(1);
	return (array);
}
