/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 17:59:13 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/20 14:26:40 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

static size_t	ft_envcpy_add(char **arg, char **env)
{
	size_t	i;
	size_t	j;
	size_t	n;

	if (!arg || !env)
		return (0);
	j = 0;
	while (arg[j] && ft_isin('=', arg[j]))
	{
		n = (size_t)ft_strlento(arg[j], '=') + 1;
		i = 0;
		while (env[i] && ft_strncmp(env[i], arg[j], n))
			i++;
		if (env[i])
			free(env[i]);
		else
			env[i + 1] = NULL;
		env[i] = ft_strdup(arg[j]);
		j++;
	}
	return (j);
}

static void		ft_envcpy(t_shell *sh, char **arg, char **env)
{
	size_t	i;
	char	**newenv;
	t_com	com;

	if ((i = 1) && arg[0] && !ft_strcmp(arg[0], "-i"))
		newenv = ((char**)ft_memalloc(sizeof(char*)));
	else
	{
		i = ft_tablen(env) + ft_tablen(arg);
		if (!(newenv = (char**)ft_memalloc(sizeof(char*) * (i + 1))))
			return ;
		i = 0;
		while (env[i++])
			newenv[i - 1] = ft_strdup(env[i - 1]);
		i = ft_envcpy_add(arg, newenv);
	}
	ft_bzero(&com, sizeof(t_com));
	com.cli = &arg[i];
	sh->env = newenv;
	if (newenv && !arg[i])
		ft_env(sh, &arg[i], &newenv);
	else if (newenv)
		exec_cli(sh, &com);
	ft_free_dblechar_tab(newenv);
	sh->env = env;
}

void			ft_env(t_shell *sh, char **arg, char ***aenv)
{
	char	**env;

	if (!arg || !aenv || !(env = *aenv))
		return ;
	if (!*arg || !arg[1])
	{
		while (*env)
		{
			ft_printf("%s\n", *env);
			env++;
		}
		(void)sh;
	}
	else
		ft_envcpy(sh, &arg[1], env);
	exit(EXIT_SUCCESS);
}
