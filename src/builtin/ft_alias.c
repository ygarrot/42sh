#include "../../includes/sh.h"

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
	void *tmp;
	t_btree **root;
	int	len;

	root = alias_tb();
	if (!arg || !env)
	{
		ft_printf("alias: An error occured\n");
		return ;
	}
	if (!arg[1])
		print_alias(root);
	if ((len = ft_charchr('=', arg[1])) >= 0)
	{
		tmp = ft_strndup(arg[1], len);
		ft_set_hash(root, tmp, &(arg[1])[len + 1]);
		ft_memdel((void**)&tmp);
		
	}
	else
		if ((root = btree_search_item(*root, &arg[1], ft_hashcmp)))
			ft_printf("%s\n", ((char**)(*root)->item)[1]);
}
