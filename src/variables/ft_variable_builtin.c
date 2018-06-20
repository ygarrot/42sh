/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variable_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 12:41:24 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/20 18:00:57 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	ft_variable_builtin_pars(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i] && !ft_isin(str[i], VAR_LIM))
		i++;
	if (str[i] == '=')
		return (i > 0 ? i : -1);
	if (str[i] != '[' || i == 0)
		return (-1);
	i++;
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == ']' && str[i + 1] == '=')
		return (i + 1);
	return (-1);
}

static void	ft_variable_builtin_(char *str, int i)
{
	int					j;
	t_variable_array	var;
	t_list				*lst;

	j = 1;
	if (!(var.str = ft_strdup(&str[i + 1])))
		return ;
	while (i > 0 && str[i] != '[')
		i--;
	if (i == 0 || str[i + 1] < '0' || str[i + 1] > '9')
		return ;
	var.index = 0;
	while (str[i + j] != ']' && str[i + j])
		var.index = var.index * 10 + str[i + j++] - '0';
	if (!(lst = ft_lstnew((void*)&var, sizeof(t_variable_array))))
		return ;
	ft_variableadd(ft_strndup(str, i), (void*)lst, 2, 0);
}

void		ft_variable_builtin(char *str)
{
	char		**setenv;
	int			i;
	char		***env;
	int			deported;
	t_variable	*var;

	if ((i = ft_variable_builtin_pars(str)) == -1)
		return ;
	deported = 0;
	if (str[i - 1] == ']')
		ft_variable_builtin_(str, i);
	if (str[i - 1] == ']')
		return ;
	str[i] = 0;
	var = ft_variableget(str);
	if ((var && var->deported && var->deep == 1) || (ft_getenv_fromroot(str)
			&& (!var || var->deep == 1)))
	{
		deported = 1;
		setenv = (char*[4]){"setenv", str, &str[i + 1], 0};
		if ((env = ft_storeenv(0, ft_subshell_get())))
			ft_setenv(setenv, env);
	}
	ft_variableadd(ft_strdup(str), (void*)ft_strdup(&str[i + 1]), 1, deported);
	str[i] = '=';
}
