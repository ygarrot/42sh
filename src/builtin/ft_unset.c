/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:17:26 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/03 15:45:16 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_unset(char **arg, char ***env)
{
	t_btree		**root;
	t_variable	cmp;
	t_variable	*tmp;
	char		**unsetenv;

	if (!arg || !env || !*env || !*arg)
		return ;
	if (!(root = ft_variable()))
		return ;
	ft_bzero((void*)&cmp, sizeof(t_variable));
	if (!(cmp.name = arg[1]))
	{
		ft_putstr_fd("21sh : unset VARNAME\n", 2);
		return ;
	}
	tmp = btree_search_item(*root, (void*)&cmp, &ft_variablecmp);
	if (tmp && tmp->deported)
	{
		unsetenv = (char*[3]){"unsetenv", arg[1], 0};
		ft_unsetenv(unsetenv, env);
	}
	btree_remove_data(root, (void*)&cmp, ft_variablecmp, ft_variabledel);
}
