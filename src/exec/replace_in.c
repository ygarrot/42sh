
#include "../../includes/sh.h"

t_tb	*get_last(t_tb *list, int *len)
{
	if (!list)
		return (NULL);
	if (list->next && ++*len)
		return (get_last(list->next, len));
	return (list);
}

void recc_repl(t_tb **list)
{
	if (!list)
		return ;
	if ((*list)->next)
	{
		(*list)->str = (*list)->next->str;
		recc_repl(&(*list)->next);
	}
	else
		ft_memdel((void**)&(*list));
}

int	 split_tmp(t_com *com, t_tb **list, char *str)
{
	char	**tb;
	int		i;
	t_tb *tmp[2];

	i = -1;
	tb = ft_strsplit_comm(str, " ");
	if (!*tb || !tb[1])
	{
		ft_free_dblechar_tab(tb);
		return (0);
	}
	*tmp = (*list)->next;
	(*list)->next = NULL;
	ft_memdel((void**)&(*list)->str);
	while (tb[++i])
		add_comm(com, tb[i]);
	tmp[1] = get_last(*list, &com->len);
	tmp[1]->next = *tmp;
	ft_memdel((void**)&tb);
	return (1);
}

int	 add_glob(t_com *com, t_tb **list, char *str)
{
	if (!str || split_tmp(com, list, str))
	{
		recc_repl(list);
		return (1);
	}
	if (((*list)->glob = ft_glob(str, 0)))
		ft_memdel((void**)&(*list)->str);
	com->len += (*list)->str ? 1 : (*list)->glob->nb_paths;
	return (0);
}

void replace_in(t_shell *sh, t_com *com)
{
	t_tb	*list;
	int		i;
	char *free;

	i = 0;
	free = NULL;
	if (!(list = com->tb) || com->len < 0)
		return ;
	while (list)
	{
		free = list->str;
		list->str = ft_find_and_replace(free, "\\", 1);
		ft_memdel((void**)&free);
		arg_replace(sh, &list->str);
		replace_local(sh, &list->str, i++);
		if (!add_glob(com, &list, list->str))
			list ? list = list->next : 0;
	}
	if (!com->len)
		ft_memdel((void**)&com->cli);
	else
		epur_tb(com, com->len);
}
