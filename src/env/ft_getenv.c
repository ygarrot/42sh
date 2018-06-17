/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 16:21:45 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/17 16:21:56 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char	*ft_getenv_fromroot(char *str)
{
	char	***env;
	size_t	i;
	size_t	j;

	if (!(i = ft_strlen(str)))
		return (0);
	if (!(env = ft_storeenv(0, ft_subshell_get())))
		return (0);
	if (!*env)
		return (0);
	j = 0;
	while (env[0][j] &&
		(ft_strncmp(str, env[0][j], i) || env[0][j][i] != '='))
		j++;
	if (env[0][j])
		return (&env[0][j][i + 1]);
	return (0);
}

int		ft_recoverenv(char ***env)
{
	char	***tmp;

	tmp = ft_storeenv(0, ft_subshell_get());
	if (env && tmp)
		*env = *tmp;
	if (!env || !*env || !tmp)
		return (-1);
	return (0);
}
