/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_storeenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 13:06:27 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/15 16:58:14 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void	ft_free_tenv(t_env *el)
{
	if (el)
	{
		if (el->env)
			ft_free_dblechar_tab(el->env[0]);
		free(el->env);
		el->env = 0;
		free(el);
	}
}

t_env	*ft_storeenv_alloc(char **env, int i)
{
	t_env	*el;

	if (!(el = ft_memalloc(sizeof(t_env))))
		return (0);
	el->i = i;
	if (!(el->env = ft_memalloc(sizeof(char**))))
	{
		free(el);
		return (0);
	}
	el->env[0] = env;
	return (el);
}

char	***ft_storeenv(char **env, int i)
{
	static t_list	*lst = 0;
	t_env			*el;

	if (!lst && !env)
		return (0);
	el = (env ? ft_storeenv_alloc(env, i) : 0);
	if (env && !el)
		return (0);
	if (!lst && env)
	{
		lst = ft_lstnewc((void*)el, sizeof(t_env));
		return (((t_env*)(lst->content))->env);
	}
	while (lst && lst->next && ((t_env*)(lst->content))->i != i)
		lst = lst->next;
	if (env && lst && ((t_env*)(lst->content))->i == i)
	{
		ft_free_tenv((t_env*)(lst->content));
		lst->content = el;
	}
	else if (env && lst)
		lst->next = ft_lstnew((void*)&el, sizeof(t_env));
	if (((t_env*)(lst->content))->i != i)
		return (0);
	return (((t_env*)(lst->content))->env);
}

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
