/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 14:42:28 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/13 11:29:31 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void	ft_cdvar(char *old, char ***env)
{
	char	*tmp[4];

	tmp[0] = "ft_setenv";
	tmp[3] = NULL;
	tmp[1] = "OLDPWD";
	tmp[2] = old;
	ft_setenv(tmp, env);
	tmp[1] = "PWD";
	tmp[2] = getcwd(NULL, 1);
	ft_setenv(tmp, env);
	ft_strdel(&(tmp[2]));
}

static void	ft_cdaux(char **a, char ***env, char **prev)
{
	char	tmp[256];

	getcwd(tmp, 256);
	if (chdir(a[1]) == -1)
		ft_error("21sh: cd: Can't access ", a[1]);
	else
	{
		ft_strdel(prev);
		if (prev)
			*prev = ft_strdup(tmp);
		ft_cdvar(*prev, env);
	}
}

static void	ft_cdback(char *a, char ***env, char **prev)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	if (a)
		ft_error("21sh: cd: Too many arguments (1 expected)", 0);
	if (a || !prev)
		return ;
	if (!*prev)
		*prev = ft_strdup(ft_getenv_fromroot("OLDPWD"));
	tmp = getcwd(tmp, 1);
	i = chdir(*prev);
	ft_strdel(i == -1 ? &tmp : prev);
	if (i == -1)
		ft_error("21sh: cd: Can't access %s\n", *prev);
	else
	{
		*prev = tmp;
		if (*prev)
			ft_cdvar(*prev, env);
	}
}

void		ft_cd(char **a, char ***env)
{
	static char	*prev;
	char		*tmp;
	char		*s;

	tmp = NULL;
	if (!a[0] || !a[1])
	{
		tmp = getcwd(tmp, 256);
		s = ft_getenv_fromroot("HOME");
		if (!s || chdir(s) == -1)
			ft_error("21sh: cd: Can't access %s\n", s);
		else
		{
			ft_strdel(&prev);
			prev = ft_strdup(tmp);
			if (prev)
				ft_cdvar(prev, env);
		}
		ft_strdel(&tmp);
	}
	else if (a[2] || !ft_strcmp(a[1], "-"))
		ft_cdback(a[2], env, &prev);
	else
		ft_cdaux(a, env, &prev);
}
