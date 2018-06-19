/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_split_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 13:14:00 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/19 13:23:41 by tcharrie         ###   ########.fr       */
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
		while (ft_isin(str[i], delim))
			i++;
		if (str[i])
			c++;
		while (!ft_isin(str[i], delim))
			i++;
	}
	return (c + 1);
}

char	**ft_read_split_array(t_read *parser, char *str)
{
	char	**array;
	int		count;
	int		i;
	char	*delim;

	if (!parser || !str || !parser->variables || !(delim = ft_read_delim()))
		return (0);
	i = 0;

	count = 0;
	if (!(array = ft_memalloc(sizeof(char*) *
			ft_read_split_count(str, delim))))
	while (str[i])
	{
		while (ft_isin(str[i], delim))
			i++;
		

	}
}
