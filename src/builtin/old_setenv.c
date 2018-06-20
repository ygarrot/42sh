/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 16:56:40 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/12 13:04:13 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

static void	ft_setenvnew_aux(char ***env, char **tb, char *str)
{
	int	i;

	i = -1;
	while (env[0][++i])
		tb[i] = env[0][i];
	tb[i++] = str;
	tb[i] = 0;
	free(*env);
	*env = tb;
}

static void	ft_setenvnew(char ***env, char *var, char *value)
{
	int		i;
	int		j;
	char	*str;
	char	**tb;

	i = 0;
	while (env[0][i])
		i++;
	if (!(tb = (char**)malloc(sizeof(char*) * (i + 2))))
		return ;
	if (!(str = (char*)malloc(ft_strlen(var) + (value ? ft_strlen(value) : 0)
					+ 2)))
		return ;
	i = -1;
	while (var[++i])
		str[i] = var[i];
	str[i++] = '=';
	j = 0;
	while (value && value[j])
		str[i++] = value[j++];
	str[i] = 0;
	ft_setenvnew_aux(env, tb, str);
}

static void	ft_setenvaux(char **a, char **env)
{
	size_t	i;
	char	*tmp;

	if (!(tmp = (char*)malloc(sizeof(char) * (ft_strlen(a[1]) + 1))))
	{
		ft_error("setenv: An error occured", 0);
		return ;
	}
	i = 0;
	while (a[1][i])
	{
		tmp[i] = a[1][i];
		i++;
	}
	tmp[i] = '=';
	tmp[i + 1] = 0;
	(void)env;
	ft_strdel(&tmp);
}

void		ft_setenv(char **arg, char ***env)
{
	int		i;
	size_t	j;

	i = 0;
	if (!arg || !env || !*env)
		ft_printf("\n");
	else if (!arg[1])
		ft_putendl_fd("minishell: setenv VARNAME [VARVALUE]", 2);
	else
	{
		j = ft_strlen(arg[1]);
		while (env[0][i] && (ft_strncmp(arg[1], env[0][i], j) ||
					env[0][i][j] != '='))
			i++;
		if (env[0][i] && !arg[2])
			env[0][i][ft_strlento(env[0][i], '=') + 1] = 0;
		else if (env[0][i] && arg[2])
			ft_setenvaux(arg, *env);
		else
			return (ft_setenvnew(env, arg[1], arg[2]));
	}
}
