#include "../../includes/sh.h"


#define PARENTH 0xF00000

void	free_op(t_do_op *tmp)
{
	//	ft_printf("[%s]\n", tmp->content);
	tmp->next ? tmp->next->prev = tmp->prev : 0;
	tmp->prev ? tmp->prev->next = tmp->next : 0;
	ft_memdel((void**)&tmp->content);
	ft_memdel((void**)&tmp);
}

# define BIT (char *[14]){"<<", ">>", "|", "||", "&&", "&", "^", "~"}
/*
int browse_list(t_do_op *list, int mode)
{
	t_do_op *begin;
	t_do_op *tmp;

	begin = list;
	while (list)
	{
		if (!mode && (list->code == 9 || list->code == 10))
			list->code == 9 ? list->value++ : list->value--;
		if (!mode && list->code == PARENTH)
		{
			list->value = parse_op(list->content);
			list->is_set = 1;
		}
		list = list->next;
	}
	return (browse_last(begin));
}
*/
t_do_op	*pre_op(t_do_op *list)
{
	t_do_op *tmp;

	if (*list->content == '(')
	{
		ft_printf("ici\n");
		ft_strcpy(list->content, &list->content[1]);
		list->value = parse_op(list->content);
		list->is_set = 1;
		return (list);
	}
	if (ft_isin('=', list->content))
	{
	
	}
	tmp = list->next->next;
	list->prev->value = do_op(list->prev, list, list->next);
	list = list->prev;
	free_op(list->next->next);
	free_op(list->next);
	list->is_set = 1;
	list->next = tmp;
	return (list);
}

t_do_op	*if_function(t_do_op *list, int status)
{
	if ((status == 0 && (*list->content == '(' || !ft_strcmp(list->content, "--")|| !ft_strcmp(list->content, "++"))) ||
			(status == 1 && (!ft_strcmp(list->content, "--") || !ft_strcmp(list->content, "++"))) ||
			/*(status == 2 && (!ft_strcmp(list->content, "-") || !ft_strcmp(list->content, "+"))) ||*/
			(status == 3 && ft_isin(*list->content, "~!")) ||
			(status == 4 && !ft_strcmp(list->content, "**")) ||
			(status == 5 && ft_isin(*list->content, "*/")) ||
			(status == 6 && ft_isin(*list->content, "-+")) ||
			(status == 7 && !ft_strcmp(list->content, "++")) ||
			(status == 8 && !ft_strcmp(list->content, "==")) ||
			(status == 9 && !ft_strcmp(list->content, "^")) ||
			(status == 10 && !ft_strcmp(list->content, "|")) ||
			(status == 11  && !ft_strcmp(list->content, "&&")) ||
			(status == 12 && !ft_strcmp(list->content, "||")) ||
			(status == 13 && !ft_strcmp(list->content, "?")))
		list = pre_op(list);
	return(list);
}

int	the_order(t_do_op *begin)
{
	int i;
	t_do_op *list;

	i = -1;
	while (begin && begin->next && ++i < 17)
	{
		list = begin;
		while (list && list->next)
		{
			list = if_function(list, i);
			list && list->next ? list = list->next : 0;
		}
	}
	return (begin ? begin->value : 0);
}

void	set_assign(t_do_op *list)
{
	while (list->next)
		list = list->next;
	while (list->prev)
	{
		if (list->code < 10 && list->code >= 0)
			list->prev->value = the_order(list);
		list = list->prev;
	}
}

int		exec_op(char **tb)
{
	t_do_op		*list;
	t_do_op		*begin;
	int			i;

	i = -1;
	list = (t_do_op*)ft_memalloc(sizeof(t_do_op));
	begin = list;
	while (tb[++i])
	{
		tb[i + 1] ? list->next = (t_do_op*)ft_memalloc(sizeof(t_do_op)) : 0;
		list->next ? list->next->prev = list : 0;
		list->content = tb[i];
		list->code = get_sep(tb[i], OPE);
		//	ft_printf("{red}%s %d{reset}\n", tb[i], list->code);
		list = list->next;
	}
	ft_memdel((void**)&tb);
	return (the_order(begin));
	//return (browse_list(begin, 0));
}
