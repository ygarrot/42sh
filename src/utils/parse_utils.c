/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 11:39:04 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/17 10:26:38 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		skip_comm(char *str)
{
	int		i;
	char	q;

	i = 0;
	if (!str || !*str)
		return (0);
	if ((ft_isin(str[i], QUOTES) && (q = str[i++])))
	{
		while (str[i] && str[i++] != q)
		{
			i += (str[i] == '\\' && str[i + 1]);
			if (!str[i])
				return (0);
		}
	}
	if (str[i] == '\\')
		i += str[i + 1] ? 2 : 1;
	return (i);
}

int		get_sep(char *str, char **tb)
{
	int	i;

	i = -1;
	while (tb[++i] && ft_strncmp(str, tb[i], ft_strlen(tb[i])))
		;
	return (tb[i] ? i : -1);
}

/*
** strnstr pour un tbleau passé en param
** renvoie la taille de la chaine si trouvée dans le tb sinon 0
*/

char	is_sep(char *str, t_parser *par, char **tb)
{
	int		i;
	int		len;

	i = -1;
	while (tb[++i] && !ft_strnstr(str, tb[i], len = ft_strlen(tb[i])))
		;
	if (tb[i])
		ft_strcpy(par->op, tb[i][0] != '\n' ? tb[i] : "\\n");
	return (tb[i] ? len : 0);
}

/*
** recherche la premiere occurence d'une chaine du tbleau donné en param
** dans la chaine donné en second param
*/

int		search_op(char *str, char **op)
{
	int	i;
	int	ind;

	i = -1;
	while (str && str[++i])
	{
		ind = -1;
		i += skip_comm(&str[i]);
		while (op[++ind])
		{
			if (!ft_strncmp(&str[i], op[ind], ft_strlen(op[ind])))
				if (ft_strncmp(op[ind], "&", ft_strlen(op[ind])) || !str[i]
	|| (!ft_isin(str[i + 1], "<&") && (i <= 0 || (i >= 2 && str[i - 2] == '\\')
	|| !ft_isin(str[i - 1], "&>"))))
					return (i);
		}
		if (!str[i])
			return (-1);
	}
	return (-1);
}
