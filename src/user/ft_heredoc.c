/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 12:54:57 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/27 14:10:17 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

static void	ft_heredoc_purge_(char *str, t_parser *parser, int *i, int *j)
{
	int	k;
	int	u;
	int	v;

	u = *i;
	v = *j;
	k = ft_strlen(parser->comm);
	while (str[u] && (ft_strlento(&str[u], '\n') != k ||
			ft_strncmp(parser->comm, &str[u], k)))
	{
		while (str[u] && str[u] != '\n')
			str[v++] = str[u++];
		if (str[u] == '\n')
			str[v++] = str[u++];
	}
	if (ft_strlento(&str[u], '\n') == k &&
				!ft_strncmp(parser->comm, &str[u], k))
		u += k + 1;
	*i = u;
	*j = v;
}

void		ft_heredoc_purge(char *str, int size, t_parser *parser)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	if (!parser || !str)
		return ;
	while (i < size && parser)
	{
		if (parser->drop == 1 && parser->comm)
			ft_heredoc_purge_(str, parser, &i, &j);
		else if (parser->drop == 2 || parser->comm == 0)
		{
			k = (str[i] != 0);
			while (str[i])
				str[j++] = str[i++];
			if (k)
				j--;
		}
		parser = parser->next;
		str[j++] = str[i++];
	}
	while (j < size)
		str[j++] = 0;
}
