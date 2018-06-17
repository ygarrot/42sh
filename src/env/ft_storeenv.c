/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_storeenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 13:06:27 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/17 16:35:06 by tcharrie         ###   ########.fr       */
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
	{
		ft_free_dblechar_tab(env);
		return (0);
	}
	el->i = i;
	if (!(el->env = ft_memalloc(sizeof(char**))))
	{
		ft_free_dblechar_tab(env);
		free(el);
		return (0);
	}
	el->env[0] = env;
	return (el);
}

char	***ft_storeenv_(t_list *lst, int i, t_env *el)
{
	while (lst && lst->next && lst->content && ((t_env*)(lst->content))->i != i)
		lst = lst->next;
	if (el && lst && (!lst->content || ((t_env*)(lst->content))->i == i))
	{
		ft_free_tenv((t_env*)(lst->content));
		lst->content = el;
	}
	else if (el && lst)
		lst->next = ft_lstnewc((void*)el, sizeof(t_env));
	if (((t_env*)(lst->content))->i != i)
		return (0);
	return (((t_env*)(lst->content))->env);
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
	if (!lst)
		return (0);
	return (ft_storeenv_(lst, i, el));
}
