int ft_alias(t_shell *sh, char **arg, char ***env)
{
	void *tmp;

	if (!arg || !env)
	{
		ft_printf("alias: An error occured\n");
		return ;
	}
	if (!*arg)
		print_alias();
	if (ft_charchr(*arg, '=') >= 0)
	{
		tmp = ft_strndup(*arg, ft_charchr(*arg, '=') + 1);
		ft_set_hash(sh->alias_tb, tmp);
		}
	else
		if ((tmp = btree_search_item(root, &key, ft_hashcmp)))
			ft_printf("%s\n", tmp[1])
}
