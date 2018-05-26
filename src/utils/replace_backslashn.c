/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_backslashn.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 15:03:59 by ygarrot           #+#    #+#             */
/*   Updated: 2018/05/18 15:29:12 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

void	replace_backslashn(char **str)
{
	int tmp;
	int i;

	i = -1;
	while ((*str)[++i])
	{
		i += skip_comm(&(*str)[i]);
		if ((*str)[i] == '\n')
		{
			tmp = i;
			while (tmp  >= 0 && (*str)[tmp] == ' ')
				tmp--;
			if (get_sep(&(*str)[tmp], SEP) >= 0)
				ft_strcpy(&(*str)[i], &(*str)[i + 1]);
		}
	}
}
