/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 12:02:43 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/21 10:47:54 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

/*
** t[0] : incrementation (src)
** t[1] : incrementation (dest)
** t[2] : sep
** t[3] : bl
** t[4] : bq
*/

char	*ft_history_parser(char *str)
{
	char	*res;
	int		t[5];

	if (!str || !*str || (str[0] == '\n' && !str[1]) ||
			!(res = (char*)ft_memalloc(ft_strlen(str) + 1)))
		return (0);
	ft_bzero((void*)t, sizeof(t));
	while (str[t[0]])
	{
		if (!t[2] && !t[3] && str[t[0]] == '\\' && str[t[0] + 1] == '\n')
			t[0] += 2;
		else if (t[3] && str[t[0]] == '\n' && !t[2] && !t[3])
			t[0]++;
		else
		{
			ft_separator(str[t[0]], &t[2], &t[3], &t[4]);
			res[t[1]++] = str[t[0]++];
		}
	}
	if (t[1] > 0)
		res[t[1] - 1] = 0;
	return (res);
}
