/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_historyfile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 13:47:57 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/12 13:08:20 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		ft_historyfile_open(void)
{
	return (open(HISTORYFILE, O_CREATE, O_APPEND, O_RDWR));
}

void	ft_historyfile_read(t_list **lst)
{
	(void)lst;
}

void	ft_historyfile_write(t_list *lst)
{
	int	fd;

	if ((fd = ft_historyfile_open()) == -1)
		return ;
	while (lst)
	{
		if (lst->content)
		{
			ft_putstr_fd((char*)(lst->content), fd);
			ft_putchar_fd('\n', fd);
		}
		lst = lst->next;
	}
}
