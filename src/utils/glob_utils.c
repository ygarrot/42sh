/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 18:43:10 by ygarrot           #+#    #+#             */
/*   Updated: 2018/05/10 16:14:19 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	true_sort(t_paths *begin, t_paths *to_add)
{
	while (begin->next)
		begin = begin->next;
	begin->next = to_add;
}

int		ft_strlento_comm(char *str, char *to_find)
{
	int i;

	i = 0;
	if (!str || !to_find)
		return (-1);
	while (str[i])
	{
		i += skip_comm(&str[i]);
		if (ft_isin(str[i++], to_find))
			return (i);
	}
	return (0);
}
