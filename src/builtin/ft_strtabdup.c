/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtabdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 12:55:00 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/12 12:55:00 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	**ft_strtbdup(char **tb)
{
	char	**dup;
	int		i;

	if (!tb)
		return (NULL);
	i = 0;
	while (tb[i])
		i++;
	if (!(dup = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = 0;
	while (tb[i])
	{
		if (!(dup[i] = ft_strdup(tb[i])))
		{
			while (i > 0 && --i >= 0)
				free(dup[i]);
			free(dup);
			return (NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
