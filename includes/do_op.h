/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 16:51:54 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/16 18:06:35 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DO_OP_H
# define DO_OP_H


typedef struct s_do_op 
{
    struct s_do_op *prev;
    struct s_do_op *next;
    char	*content;
	bool	is_set;
	int		is_spec;
	int		is_inc;
	int		sign;
	int		value;
	int		code;
}		t_do_op;


# define OPE (char *[16]){"<<", ">>", "||", "&&","**",  "|", "&", "^", "~", "+", "-", "/", "*", "%"}
# define CREMENT (char *[3]){"--", "++"}

# define SHIFT (char *[3]){ "<<", ">>"}
# define COMP (char *[7]){"<=", ">=", "<", ">", "==", "!="}
# define HCOMP (char *[5]){ "<=", ">=", "<", ">"}
# define LCOMP (char *[3]){ "==", "!="}


/*
** math functions
*/

int		exe_assign(t_do_op *to_ass,char *str, int value);
int		is_incre(t_do_op **b, t_do_op*a);
int	del_after_exec(t_do_op **list);
int	error_do_op(char *str);
t_do_op **begin_op(t_do_op **beg);
int		unaire(t_do_op **a);
void	increment(t_do_op *a, int i);
void	set_op_variable(char *key, int value);
char	**all_op(int index);
t_do_op	*del_ternary(t_do_op **c);
void	free_op(t_do_op **tmp);
char	*parse_op(char *str);
int (**f_opget(void))(int, int);
int		calc_op(char **op_tb);

int		check_op(char *str);
int		is_local(char *str);
int		get_value(t_do_op *tmp);
int		*do_op(t_do_op *a, t_do_op *op, t_do_op *b);
int		browse_last(t_do_op *list);
char		*exec_op(char **tb);
int		parenth(char **str, int i, char rep, bool recc);

/*
** bitwise
*/

int		ft_left_shift(int a, int b);
int		ft_right_shift(int a, int b);
int		ft_log_or(int a, int b);
int		ft_log_and(int a, int b);
int		ft_and(int a, int b);
int		ft_or(int a, int b);
int		ft_xor(int a, int b);
int		ft_bitneg(int a, int b);

/*
** classic op
*/

int		ft_mult(int a, int b);
int		ft_summ(int a, int b);
int		ft_div(int a, int b);
int		ft_sub(int a, int b);
int		ft_mod(int a, int b);

int		skip_char(char *str, char *to_skip);
int		ft_occiter2(char *str, int (*f)(int));

/*
** comp op
*/

void	free_do_op(t_do_op **beg);
int		ft_ternary(t_do_op *a, t_do_op *b, int *result);
int		ft_comp_infe(int a, int b);
int		ft_comp_supe(int a, int b);
int		ft_comp_inf(int a, int b);
int		ft_comp_sup(int a, int b);
int		ft_comp_neg(int a, int b);
int		ft_comp(int a, int b);

#endif
