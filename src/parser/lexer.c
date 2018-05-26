/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 15:40:03 by ygarrot           #+#    #+#             */
/*   Updated: 2018/05/18 11:36:14 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

/*
** les deux fonctions en dessous permettent de compter le nombre de here_doc
** split les commandes en fonction de tout les type de separateur.
** Pas super clean mais évite d'allouer de la mem
** Gere les erreurs de parsing, ne gere (surement) pas toutes les erreurs
*/

int			get_hdoc(char *str, int i, t_parser *par)
{
	int		hdoc;
	int		red;
	char	*todel;

	if ((hdoc = is_sep(&str[i], par, REDI)))
	{
		red = get_sep(&str[i], REDI);
		if ((i += hdoc) && !red)
		{
			while (str[i] == ' ')
				i++;
			todel = ft_strndup(&str[i],
		(hdoc = search_op(&str[i], HD) >= 0 ||
		(hdoc = ft_isin(str[i], NORM)) ? hdoc + 1 : ft_strlen(&str[i])));
			par = push_front(par, ft_find_and_replace(todel, "\\", 1), 0);
			ft_memdel((void**)&todel);
		}
		while (str[i] == ' ')
			i++;
		if (((red == 2 || red == 3) && str[i] != '-' && !ft_isdigit(str[i]))
	|| ((is_sep(&str[i], par, SEP) || is_sep(&str[i], par, REDI))))
			return (-1);
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
	return (i || !str[i] ? i + sep : -1);
}

t_parser	*count_parser(char *str)
{
	int			i;
	t_parser	*par;
	int			sep;

	i = 0;
	mallcheck(par = (t_parser*)ft_memalloc(sizeof(t_parser)));
	while (str[i] && str[i] != '\n')
	{
		while (str[i] && str[i] == ' ')
			i++;
		sep = sizeof_comm(&str[i], par);
		if (sep < 0)
		{
			ft_printf("yosh: parse error near `%s'\n", par->op);
			free_parser(par);
			return (NULL);
		}
		i += sep;
	}
	return (par);
}
