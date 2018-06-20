/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 12:38:29 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/20 17:35:48 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	**ft_read_split_check(t_read *parser, char **array)
{
	int	i;

	if (!parser || !parser->variables || !array || !parser->variables[0])
	{
		ft_free_dblechar_tab(array);
		return (0);
	}
	i = 0;
	while (parser->variables[i])
	{
		if (!array[i])
		{
			ft_free_dblechar_tab(array);
			return (0);
		}
		i++;
	}
	return (array);
}

char	*ft_read_split_word(t_read *parser, char *str, char *delim, int y)
{
	int	i;
	int	j;
	int	bl;

	(void)parser;
	i = 0;
	j = 0;
	bl = 0;
	if (y)
	{
		i = (i > 0 ? i - 1 : 0);
		while (i > 0 && ft_isin_unicode(&str[i], delim))
			i -= ft_lenchar_l(str, i);
		i = (i >= 0 && !ft_isin_unicode(&str[i], delim) ? i + 1 : i);
		return (i > 0 ? ft_strndup(str, i) : ft_strdup(""));
	}
	while (str[i] && (bl || !ft_isin_unicode(&str[i], delim)))
	{
		bl = (parser->bl_active && !bl && str[i] == '\\');
		i += ft_lenchar_r(str, i);
	}
	return (i > 0 ? ft_strndup(str, i) : ft_strdup(""));
}

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
	while (parser->variables[count])
	{
		while (str[i] && ft_isin_unicode(&str[i], delim))
			i += ft_lenchar_r(str, i);
		if (parser->variables[count + 1] == 0 || !str[i])
			array[count++] = ft_read_split_word(parser, &str[i], delim, 1);
//			array[count++] = ft_strdup(str[i] ? &str[i] : "");
		else
		{
			array[count++] = ft_read_split_word(parser, &str[i], delim, 0);
//			array[count++] = ft_strndup(&str[i], ft_read_split_lenword(parser,
//					&str[i], delim));
			i += ft_read_split_lenword(parser, &str[i], delim);
		}
	}
	return (ft_read_split_check(parser, array));
}
