/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 15:40:03 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/20 18:20:50 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

/*
** les deux fonctions en dessous permettent de compter le nombre de here_doc
** split les commandes en fonction de tout les type de separateur.
** Pas super clean mais évite d'allouer de la mem
** Gere les erreurs de parsing, ne gere (surement) pas toutes les erreurs
*/

void		add_aliases(char **str, char free)
{
	char		**all_op;
	char		**tb;
	char		**tmp;
	t_btree		**root;

	root = alias_tb();
	all_op = (char *[14]){"||", "&&", "|", "&", ";", ">>",
	"<<", ">&", "<&", "\n", " ", "<", ">", 0};
	tb = ft_custom_split(*str, all_op, 1);
	if ((tmp = btree_search_item(*root, &tb[0], ft_hashcmp)))
	{
		ft_memdel((void**)&tb[0]);
		tb[0] = ft_strdup(tmp[1]);
	}
	free ? ft_memdel((void**)&(*str)) : 0;
	*str = ft_str_tabjoin((const char**)tb);
	ft_free_dblechar_tab(tb);
}

int			get_hdoc(char *str, int i, t_parser *par)
{
	int		hdoc;
	int		red;
	char	*todel;

	if ((hdoc = is_sep(&str[i], par, REDI)))
	{
		red = get_sep(&str[i], REDI);
		i += hdoc;
		while (str[i] == ' ')
			i++;
		if (((red == 2 || red == 3) && str[i] != '-' && !ft_isdigit(str[i]))
			|| ((is_sep(&str[i], par, SEP) || is_sep(&str[i], par, REDI))))
			return (-1);
		if (!red)
		{
			hdoc = ft_strlento_comm(&str[i], ENDWORDVIS) - 1;
			todel = ft_strndup(&str[i], hdoc < 0 ? ft_strlen(&str[i]) : hdoc);
			par = push_front(par, ft_find_and_replace(todel, "\\", 1), 0);
			i += hdoc;
			ft_memdel((void**)&todel);
		}
		return (i);
	}
	return (i + 1);
}

int			sizeof_comm(char *str, t_parser *par)
{
	int		i;
	char	sep;

	i = 0;
	sep = 0;
	while (str[i] && !(sep = is_sep(&str[i], par, SEP)))
	{
		i += skip_comm(&str[i]);
		i = get_hdoc(str, i, par);
		if (i < 0)
			return (-1);
	}
	par->wait = get_sep(&str[i], SEP);
	par->wait = par->wait >= 0 && par->wait < 3 ? 1 : 0;
	if (str[i] && (str[i] == ';' || ft_strnstr(&str[i], ";;", 2)))
		return (!ft_strnstr(&str[i], ";;", 2) ? i | 1 : -1);
	return (i || !str[i] || str[i] == '\n' ? i + sep : -1);
}

t_parser	*count_parser(char **ptr, char free)
{
	int			i;
	t_parser	*par;
	int			sep;
	char		*str;

	if (!(i = 0) && check_bracket(*ptr) < 0)
	{
		free ? ft_memdel((void**)&(*ptr)) : 0;
		return (NULL);
	}
	add_aliases(ptr, free);
	mallcheck(par = (t_parser*)ft_memalloc(sizeof(t_parser)));
	while ((str = *ptr) && str[i] && str[i] != '\n')
	{
		while (str[i] && str[i] == ' ')
			i++;
		if ((sep = sizeof_comm(&str[i], par)) < 0 && (i += sep || 1))
		{
			ft_error("yosh: parse error near ", par->op);
			ft_memdel((void**)&(*ptr));
			free_parser(par);
			return (NULL);
		}
	}
	return (par);
}
