/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 16:18:21 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/12 12:48:00 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		ft_echo(char **arg, char ***en)
{
	size_t	i;
	size_t	j;
	char	**env;

	env = *en;
	i = 0;
	if (arg && env && *arg)
	{
		arg++;
		while (*arg)
		{
			j = 0;
			while (arg[0][j])
			{
				if (i || arg[0][j] != '\\')
					ft_printf("%c", arg[0][j]);
				i = !i && arg[0][j++] == '\\';
			}
			arg++;
			if (*arg)
				ft_printf(" ");
		}
	}
	ft_printf("\n");
	exit(0);
}
