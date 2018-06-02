#include "../../includes/sh.h"


#define PARENTH 0xF00000

/*
typedef struct s_do_op 
{
    struct s_do_op *prev;
    struct s_do_op *next;
    char *content;
	bool	is_set;
	int		value;
	int		code;
}		t_do_op;
*/

void	free_op(t_do_op *tmp)
{
//	ft_printf("[%s]\n", tmp->content);
	tmp->next ? tmp->next->prev = tmp->prev : 0;
	tmp->prev ? tmp->prev->next = tmp->next : 0;
	ft_memdel((void**)&tmp->content);
	ft_memdel((void**)&tmp);
}

# define BIT (char *[14]){"<<", ">>", "|", "||", "&&", "&", "^", "~"}

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
		if ((!mode && get_sep(list->content, BIT) >= 0)
				|| (mode && list->code > 10 && list->code < 14))
		{
			tmp = list->next->next;
			list->prev->value = do_op(list->prev, list, list->next);
			list = list->prev;
			free_op(list->next->next);
			free_op(list->next);
			list->is_set = 1;
			list->next = tmp;
		}
		list = list->next;
	}
	if (!mode)
		browse_list(begin, 1);
	return (mode ? 0 : browse_last(begin));
}

void	set_assign(t_do_op *list)
{
	while (list->next)
		list = list->next;
	while (list->prev)
	{
		if (list->code < 10 && list->code >= 0)
			list->prev->value = browse_list(list, 0);
		list = list->prev;
	}
}

int		browse_last(t_do_op *list)
{
	t_do_op	*tmp;
	int		res;

	if (!list)
		return (0);
	if (!list->next)
		return (list->value);
	tmp = list;
	list->value = do_op(list, list->next, list->next->next);
	list = list->next->next->next;
	while (list)
	{
		tmp->value = do_op(tmp, list, list->next);
		list = list->next->next;
	}
	return (tmp->value);
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
		if (ft_charchr('(', tb[i]) >= 0)
		{
			list->code = PARENTH;
			ft_strcpy(list->content, &list->content[1]);
		}
	//	ft_printf("{red}%s %d{reset}\n", tb[i], list->code);
		list = list->next;
	}
	ft_memdel((void**)&tb);
	return (browse_list(begin, 0));
}
