/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 16:56:40 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/26 16:03:31 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

int			ft_setenv_new(char ***env, char *str, char *value)
{
	size_t	i;
	size_t	j;
	int		k;
	char	**new;

	i = 0;
	while (env[0][i])
		i++;
	if (!(new = (char**)malloc(sizeof(char*) * (i + 2))))
		return (0);
	i = 0;
	k = 0;
	j = ft_strlen(str);
	while (env[0][i] && (ft_strncmp(env[0][i], str, j) || env[0][i][j] != '='))
		new[k++] = env[0][i++];
	new[i] = value;
	i += (env[0][i] == 0 ? 0 : 1);
	ft_strdel(&env[0][k]);
	while (env[0][i])
		new[k++ + 1] = env[0][i++];
	new[k + 1] = 0;
	free(*env);
	*env = new;
	return (0);
}

void		ft_setenv(char **arg, char ***env)
{
	char	*value;

	env = ft_storeenv(0);
	if (!arg || !env || !*env)
		write(STDOUT_FILENO, "\n", 1);
	else if (!*arg || !arg[1])
		ft_putendl_fd("21sh: setenv VARNAME [VARVALUE]", 2);
	else
	{
		if ((value = (char*)malloc(ft_strlen(arg[1]) + ft_strlen(arg[2]) + 2)))
		{
			value[0] = 0;
			ft_strcat(value, arg[1]);
			ft_strcat(value, "=");
			if (arg[2])
				ft_strcat(value, arg[2]);
		}
		if (!value || ft_setenv_new(env, arg[1], value) == -1)
		{
			ft_strdel(&value);
			ft_errorlog("Failed to insert an element in the env");
			ft_putstr_fd("Failed to insert an element in the env\n", 2);
		}
	}
}
