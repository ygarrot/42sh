/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 12:38:29 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/16 11:59:53 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_read_split_lenword(t_read *parser, char *str)
{
	int	i;
	int	bl;

	i = 0;
	bl = 0;
	while (str[i] && (bl || !ft_isin(str[i], " \n\r\f\v\t")))
	{
		bl = (str[i] == '\\' && !bl && parser->bl_active);
		i++;
	}
	return (i);
}

int		ft_read_split_countword(t_read *parser, char *str)
{
	int	i;
	int	bl;
	int	count;

	i = 0;
	bl = 0;
	count = 0;
	while (str[i])
	{
		while (!bl && str[i] && ft_isin(str[i], " \n\t\r\f\v"))
			i++;
		if (str[i])
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

	count = ft_read_split_countword(parser, str);
	if (!(array = (char**)ft_memalloc(count + 1)))
		return (0);
	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && ft_isin(str[i], " \t\n\v\r\f"))
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
