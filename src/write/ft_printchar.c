/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 14:52:44 by tcharrie          #+#    #+#             */
/*   Updated: 2018/05/26 12:57:42 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

int		ft_getdown(void)
{
	int	y;

	y = tputs(tgetstr("sf", 0), 0, writechar);
	return (y == ERR ? -1 : 1);
}

/*
** Un appel à cette fonction est une demande d'afficher le premier
** caractere de str à la position actuelle dans line & l'affiche à l'écran
** À la fin de la fonction elle meme (sanf printinsert)
** ¶La chaine de line est modifiée en conséquence et val[0] avancé
** ¶l'affichage est fait ssi on ajoute un caractère à la fin de la chaîne
*/

int		ft_printchar(t_line *line, char *str, int *val)
{
	char	*tmp;

	tmp = (val[4] ? line->line : line->eof);
	if (!str || !line || !val)
		return (-1);
	val[9] = ft_lenchar_r(str, 0);
	if (str[0] == '\n' && ft_move_toend(line, val) == -1)
		return (-1);
	if ((val[10] = val[0] + val[9] + ft_strlen(&tmp[val[0]])) + 5 >=
		(val[4] ? line->size_line : line->size_eof))
		if (ft_realloc_line(line, val, (val[10] + 30)) == -1)
			return (-1);
	tmp = (val[4] ? line->line : line->eof);
	if (ft_insert_noalloc(&tmp[val[0]], str, ft_lenchar_r(str, 0)) == -1)
		return (-1);
	val[0] += ft_lenchar_r(str, 0);
	ft_printf("{whiteblack}%.*s", ft_lenchar_r(str, 0), str);
	if ((val[6] = tgetnum("co")) <= 0)
		return (-1);
	val[9] = ft_lenline_v(tmp, val[0]);
	if (val[9] && val[9] % val[6] == 0)
		ft_getdown();
	return (tmp[val[0]] ? ft_printinsert(line, val) : 1);
}

/*
** Affiche le premier caractère et appelle ft_printdec si le caractère de
** fin de ligne a été effacé dans l'opération
*/

int		ft_printinsert(t_line *line, int *val)
{
	char	*com;
	int		loc[2];

	if (!val || !line || (val[6] = tgetnum("co")) <= 1 || !tgetstr("le", 0))
		return (-1);
	if ((val[7] = tgetnum("li")) <= 1)
		return (-1);
	com = (val[4]) ? (line->line) : (line->eof);
	if (ft_getpos(loc, &loc[1]))
		return (-1);
	tputs(tgetstr("cd", 0), 0, writechar);
	val[9] = ft_lenline_v(com, val[0]);
	val[11] = ft_strlento(&com[val[0]], '\n');
	if (com[val[0] + val[11]] == '\n')
		val[11]++;
	val[12] = ft_lennchar_r(com, val[0], val[6] - (val[9] % val[6]));
	if (val[12] < val[11])
		val[11] = val[12];
	val[10] = ft_lennline(&com[val[0] + val[11]], (val[7] - loc[0]), val[6]);
	if (com[val[0] + val[11] - 1] == '\n' &&
			val[12] >= val[11] && loc[0] == val[7])
		val[11]--;
	ft_printf("{whiteblack}%.*s", val[11] + val[10], &com[val[0]]);
	return (ft_goto(loc[0], loc[1]));
}
