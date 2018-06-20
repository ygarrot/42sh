/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 12:18:36 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/20 20:30:23 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

void		alias_file(t_shell *sh)
{
	char	*line[4];
	int		tb[3];
	t_line	line_s;

	*line = ft_strjoin(ft_getenv_fromroot("HOME"), "/.42shrc");
	*line ? tb[0] = open(*line, O_RDWR) : 0;
	ft_memdel((void**)&(*line));
	if (!*line || tb[0] < 0)
		return ;
	mallcheck(*line = ft_memalloc(4096 * sizeof(char)));
	line[2] = ft_strnew(1);
	while ((tb[1] = read(*tb, *line, 4096)) >= 0)
	{
		(*line)[tb[1]] = '\0';
		line[3] = ft_strjoin(line[2], *line);
		ft_memdel((void**)&line[2]);
		line[2] = line[3];
		if (!tb[1])
			break ;
	}
	line_s.eof = NULL;
	line_s.line = line[3];
	hard_split(sh, &line_s);
	ft_memdel((void**)&(*line));
	ft_memdel((void**)&line_s.line);
}

t_btree		**alias_tb(void)
{
	static t_btree	*alias_tb = 0;

	if (!alias_tb)
		mallcheck(alias_tb = (t_btree*)ft_memalloc(sizeof(t_btree)));
	return (&alias_tb);
}

void		print_alias(t_btree **root)
{
	char	**content;

	if (!root || !*root)
		return ;
	content = (*root)->item;
	if (content)
		ft_printf("%s='%s'\n", *content, content[1]);
	if ((*root)->left)
		print_alias(&(*root)->left);
	if ((*root)->right)
		print_alias(&(*root)->right);
}

void		ft_alias(char **arg, char ***env)
{
	void	*tmp;
	t_btree **root;
	int		len;

	(void)env;
	root = alias_tb();
	if (!arg ||
	(arg && (!ft_strcmp(arg[1], "alias") || !ft_strcmp(arg[1], "unalias"))))
	{
		ft_error("alias: An error occured\n", 0);
		return ;
	}
	if (!arg[1] || (!ft_strcmp(arg[1], "-p") && (arg++ || 1)))
		print_alias(root);
	if ((len = ft_charchr('=', arg[1])) >= 0)
	{
		tmp = ft_strndup(arg[1], len);
		ft_set_hash(root, tmp, &(arg[1])[len + 1]);
		ft_memdel((void**)&tmp);
	}
	else if ((tmp = btree_search_item(*root, &arg[1], ft_hashcmp)))
		ft_error("%s\n", ((char**)tmp)[1]);
}
