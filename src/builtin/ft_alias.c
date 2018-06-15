#include "../../includes/sh.h"

void	alias_file(t_shell *sh)
{
	char	*line[4];
	int		tb[3];
	t_line	t_line;

	*line = getenv("HOME");
	*line = ft_strjoin(*line, "/.42shrc");
	tb[0] = open(*line, O_RDWR);
	ft_memdel((void**)&(*line));
	if (tb[0] < 0)
		return ;
	mallcheck(*line = ft_memalloc(BUFF_SIZE * sizeof(char)));
	line[2] = ft_strnew(1);
	while ((tb[1] = read(*tb, *line, BUFF_SIZE)) >= 0)
	{
		(*line)[tb[1]] = '\0';
		line[3] = ft_strjoin(line[2], *line);
		ft_memdel((void**)&line[2]);
		line[2] = line[3];
		if (!tb[1])
			break;
	}
	t_line.eof = NULL;
	t_line.line = line[3];
	hard_split(sh, &t_line);
	ft_memdel((void**)&(*line));
	ft_memdel((void**)&line[3]);
	ft_memdel((void**)&line[2]);
}

t_btree		**alias_tb(void)
{
	static t_btree	*alias_tb = 0;

	if (!alias_tb)
		mallcheck(alias_tb = (t_btree*)ft_memalloc(sizeof(t_btree)));
	return (&alias_tb);
}

void	print_alias(t_btree **root)
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

void ft_alias(char **arg, char ***env)
{
	void	*tmp;
	t_btree **root;
	int		len;

	(void)env;
	root = alias_tb();
	if (!arg)
	{
		ft_printf("alias: An error occured\n");
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
	else
		if ((tmp = btree_search_item(*root, &arg[1], ft_hashcmp)))
			ft_printf("%s\n", ((char**)tmp)[1]);
}
