/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 13:51:32 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/07 13:51:40 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

/*
** Méthode permettant d'accéder à l'historique
*/

t_list	**ft_history(void)
{
	static t_list	*lst = NULL;

	if (!lst)
		lst = ft_lstnew((void*)"", 1);
	return (&lst);
}

int		ft_history_add(char *str)
{
	t_list	**history;
	t_list	*maille;

	if (!(history = ft_history()))
		return (-1);
	if (!(maille = ft_lstnew(str, ft_strlen(str) + 1)))
		return (-1);
	maille->next = *history;
	*history = maille;
	return (1);
}

char	*ft_history_get(int pos)
{
	t_list	**adr;
	t_list	*lst;

	if (pos == 0)
		return (ft_history_cache(0, CODE_GET));
	if (pos < 0)
		return (0);
	if (!(adr = ft_history()))
		return (0);
	if (!(lst = *adr))
		return (0);
	while (--pos && lst)
		lst = lst->next;
	if (!lst || !lst->next)
		return (0);
	return ((char*)(lst->content));
}

char	*ft_history_cache(char *str, int code)
{
	static char	*save;

	if (code == CODE_RESET)
		ft_strdel(&save);
	else if (code == CODE_SET)
	{
		ft_strdel(&save);
		save = str;
	}
	else if (code == CODE_GET)
		return (save);
	return (0);
}
