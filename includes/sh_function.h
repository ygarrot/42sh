/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_function.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 19:03:40 by ygarrot           #+#    #+#             */
/*   Updated: 2018/06/20 12:51:04 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_FUNCTION_H
# define SH_FUNCTION_H
# include "sh_include.h"
# include "sh_typedef.h"

/*
** Fonction de gestion d'erreur et d'affichage divers et memoire
*/

void		ft_fatal(char *str);
char		*ft_conversion_error(int code);
char		*ft_init_aff(int *val);
int			writechar(int c);
void		ft_delline(t_line *line);
void		ft_direction_del(void *content, size_t t);
void		ft_command_del(void *c, size_t t);
void		ft_errorlog(char *str);
void		ft_delparser(t_parser **pars);

/*
** Parametrage du terminal
*/

void		ft_initialisation (char **env, t_shell *sh);
int			ft_terminal_set(t_termios *term);
int			ft_recoverenv(char ***env);
char		*ft_getenvfile(int code);
int			ft_envwrite(char *file, char **env);
void		ft_initenv(char ***env);
void		ft_init_terminal_data(void);
int			ft_setattr(void);
int			ft_terminal_reset(t_termios *term);
void		ft_initsig(void);
void		ft_sig_line(int sig);

/*
** Fonction statique
*/


int			*ft_subshell(void);
int			ft_subshell_get(void);
void		ft_subshell_set(int val);
int			*ft_fd(void);
int			ft_fd_get(void);
void		ft_fd_set(int val);

/*
** Fonction d'environnement
*/

char		***ft_storeenv(char **env, int i);
char		*ft_getenv_fromroot(char *str);
int			ft_recoverenv(char ***env);

/*
** Fonction d'historique
*/

t_list		**ft_history(void);
char		*ft_history_cache(char *str, int code);
int			ft_history_add(char *str);
char		*ft_history_get(int pos);
int			ft_move_tohist(t_line *line, int *val, int dec);
char		*ft_history_parser(char *str);

int			ft_historyfile_open(void);

/*
** Recover user entry
*/

t_line		ft_getentry(void);
int			ft_read(t_line *line, int *ta);
int			ft_read_process(t_line *line, int *val, char *tmp, t_parser *pars);
int			ft_read_newline(t_line *line, int *val, t_parser *pars);
int			ft_read_newline_eof(t_line *line, int *val, t_parser *pars);
int			ft_read_eot(t_line *line, int *val, t_parser *pars);
void		ft_heredoc_purge(char *str, int size, t_parser *parser);

int			ft_specialchar(t_line *line, char *str, int *val);
int			ft_specialchar_a(t_line *line, char *str, int *val);
int			ft_lentospecial(char *str);
int			ft_lenchar_joker(char *str);

/*
** Move on the screnn
*/

int			ft_getpos(int *x, int *y);
char		*ft_readtostr(char *str, char end, int fd, int tr);
int			ft_goto(int x, int y);

int			ft_move_left(t_line *line, int *val);
int			ft_move_right(t_line *line, int *val);
void		ft_move_up(t_line *line, int *val);
int			ft_move_down(t_line *line, int *val);
int			ft_move_tohome(t_line *line, int *val);
int			ft_move_toend(t_line *line, int *val);
int			ft_move_wordl(t_line *line, int *val);
int			ft_move_wordr(t_line *line, int *val);
int			ft_move_tolinel(t_line *line, int *val);
int			ft_move_toliner(t_line *line, int *val);
void		ft_move_up_bis(char *str, int *val, int x, int y);
void		ft_move_up_ter(char *str, int *val, int y);
int			ft_move_down_bis(char *str, int *val, int x, int y);
int			ft_move_down_ter(char *str, int *val, int y);

int			ft_scroll_down(t_line *line, int *val);
int			ft_scroll_up(t_line *line, int *val);

int			ft_lenline_c(char *str, int pos);
int			ft_lenline_v(char *str, int pos);
int			ft_lenline_col(char *str, int pos, int col);
int			ft_lenchar_l(char *str, int pos);
int			ft_lenchar_r(char *str, int pos);
int			ft_lennchar_l(char *str, int pos, int n);
int			ft_lennchar_r(char *str, int pos, int n);
int			ft_lenword_l(char *str, int pos);
int			ft_lenword_r(char *str, int pos);

/*
** Fonction d'affichage
*/

int			ft_printchar(t_line *line, char *str, int *val);
int			ft_printnchar(t_line *line, char *str, int *val, int n);
int			ft_printstr(t_line *line, char *str, int *val);
int			ft_printinsert(t_line *line, int *val);
int			ft_printdec(char *str, int *val);
int			ft_getdown(void);
int			ft_lennline(char *str, int line, int col);

int			ft_realloc_line(t_line *line, int *val, int newsize);
int			ft_insert_noalloc(char *src, char *str, int size);
size_t		ft_strlen_vis(char *str);

/*
** Fonction de suppression
*/

int			ft_erase(t_line *line, int *val);
int			ft_nerase(t_line *line, int *val, int n);
int			ft_delete(t_line *line, int *val);
int			ft_ndelete(t_line *line, int *val, int n);

int			ft_sigint(int pid);
int			ft_sigint_clear(t_line *line);

/*
** Fonction  de selection
*/

char		*ft_selected(char *str, int code);
int			ft_selected_moveleft(t_line *line, int *val);
int			ft_selected_moveright(t_line *line, int *val);
int			ft_selected_cpy(t_line *line, int *val);
int			ft_selected_paste(t_line *line, int *val);
int			ft_selected_reset(t_line *line, int *val);

/*
** Fonction de traitement de la ligne
*/

char		*ft_getline(void);
int			ft_bl_active(char *str, int pos, int sep);
void		ft_separator(char c, int *sep, int *bl, int *bq);
void		ft_separator_rev(char c, int *sep, int bl, int *bq);
int			ft_separator_active(char *str, int pos, int *sep, int *bl);

/*
** Completion
*/

int			ft_completion(t_line *line, int *val);
int			ft_completion_type(t_line *line, int *val);
int			ft_completion_reset(void);
int			ft_completion_count(int code);
int			ft_completion_lastwrite(int code, int val);
int			ft_completion_savetype(int code, int type);
char		*ft_completion_saveleft(int code, char *left);
char		*ft_completion_start(t_line *line, int *val);
int			ft_completion_startpos(char *str, int pos);
char		*ft_completion_getfilename(char *left, int loc, int bl, int sep);
char		*ft_completion_com(char *left, int loc, int bl, int sep);
char		*ft_getdir(char *str);
char		*ft_straddsep(char *str, int bl, int sep);
char		*ft_strpurgesep(char *str);

DIR			*ft_opendirfree(char *str);

/*
** Variables
*/

t_btree		**ft_variable(void);
int			ft_variableadd(char *name, void *data, int deep, int deported);
t_variable	*ft_variableget(char *name);

void		ft_variabledel(void *var);
t_variable	*ft_variable_create(char *name, void *data, int deep, int deported);
int			ft_variable_checkname(char *str);
void		ft_variable_builtin(char *str);

char		*ft_variablepars(char *str);
char		*ft_variablepar_bracket(char *str);
size_t		ft_variablelen(t_variable var);
char		*ft_variablestr(t_variable var, int pos);

int			ft_variablecmp(void *left, void *right);
int			ft_variable_arraycmp(void *left, void *right);
int			ft_variable_isdeported(char *name);

/*
** Builtin read
*/

void		ft_read_builtin(char **arg, char ***env);

void		ft_read_initstruct(t_read *data);
t_read		ft_read_parser(char **arg);
int			ft_read_parser_a(t_read *parser, char *str);
int			ft_read_parser_d(t_read *parser, char *str);
int			ft_read_parser_e(t_read *parser);
int			ft_read_parser_i(t_read *parser, char *str);
int			ft_read_parser_n(t_read *parser, char *str);
int			ft_read_parser_nn(t_read *parser, char *str);
int			ft_read_parser_p(t_read *parser, char *str);
int			ft_read_parser_r(t_read *parser);
int			ft_read_parser_s(t_read *parser);
int			ft_read_parser_t(t_read *parser, char *str);
int			ft_read_parser_u(t_read *parser, char *str);
int			ft_read_checkfd(t_read *parser, char *fd, int i);

int			ft_read_usage(t_read *parser);
int			ft_read_timeerror(char *str, t_read *parser);

int			ft_read_timer(t_read *data);
void		ft_read_timer_sig(int sig);
int			ft_read_timer_sig_interrup(int sig);

int			ft_read_initterminal(t_read *parser);
int			ft_read_terminal_reset(t_termios *term, int fd);
char		*ft_read_recover(t_read *parser);
int			ft_read_recover_init(t_read *p, int *val, size_t size, t_line *l);
int			ft_read_recover_end(char **str, t_read parser);
int			ft_read_recover_sig(char **str, t_read parser);
void		ft_read_recover_pars(t_line *l, int *val, char *buff, t_read *p);
int			ft_read_recover_execute(t_line *l, int *val, char *buff, int echo);
int			ft_read_recover_execute_a(t_line *l,
		int *val, char *buff, int echo);
void		ft_read_recover_insert(t_line *line, int *val, char *buff, int len);

void		ft_read_move_left(t_line *line, int *val);
void		ft_read_move_wordl(t_line *line, int *val);
void		ft_read_move_right(t_line *line, int *val);
void		ft_read_move_wordr(t_line *line, int *val);
void		ft_read_move_tohome(t_line *line, int *val);
void		ft_read_move_tolinel(t_line *line, int *val);
void		ft_read_move_toend(t_line *line, int *val);
void		ft_read_move_toliner(t_line *line, int *val);
void		ft_read_erase(t_line *line, int *val);
void		ft_read_delete(t_line *line, int *val);
void		ft_read_movetohist(t_line *line, int *val, int mov);
void		ft_read_move_up(t_line *line, int *val);
void		ft_read_move_down(t_line *line, int *val);

char		*ft_read_delim(void);
int			ft_read_assign(t_read *parser, char *str);
char		**ft_read_split(t_read *parser, char *str);
char		**ft_read_split_array(t_read *parser, char *str);
char		**ft_read_split_check(t_read *parser, char **array);

/*
** ...
*/

/*
** error_handling
*/

void		mallcheck(void *foo);
int			error_exec(char **argv, int is_redi);

/*
** list / erase
*/

void	init_point(t_shell *sh);
void		free_comm(t_shell *sh);
void		erase_shell(t_shell *sh);
void		free_parser(t_parser *begin);
t_parser	*push_front(t_parser *com, char *str, int type);

/*
** utils
*/

void		replace_backslashn(char **str);
char		**ft_strsplit_comm(char *str, char *split);
char		*ft_find_and_replace(char *str, char *rep, int op);
char		is_sep(char *str, t_parser *par, char **tb);
void		split_co(t_shell *sh, t_parser *c);
int			get_sep(char *str, char **tb);
int			search_op(char *str, char **op);
int			skip_comm(char *str);

/*
** parser
*/

int			sizeof_comm(char *str, t_parser *par);
t_parser	*count_parser(char **str, char free);

void		hard_split(t_shell *sh, t_line *line);
t_parser	*easy_split(t_parser *c, char *str, char isamp);
void		f_point(t_shell *sh, char **av);
void		parse_exe(t_shell *sh, char *comm, char **argv);
int			skip_double(char *str);
void		ft_parserpushback(t_parser *begin, t_parser *end);

int			ft_checkquotes(char *str);

/*
** builtin
*/

void		ft_putendv_fd(char *str, int fd);
int			ft_isbuiltin(char *path);
void		ft_builtin(char **arg, char ***env, int pid);
void		ft_echo(char **arg, char ***env);
void		ft_cd(char **arg, char ***env);
void		ft_setenv(char **arg, char ***env);
void		ft_setenvno(char **arg, char ***env);
void		ft_unsetenv(char **arg, char ***env);
void		ft_env(t_shell *sh, char **arg, char ***env);
void		ft_exit(t_shell *sh, int val);
int			ft_setenvvar(char **env, char *cur, char *var);
int			ft_strlento(char *str, char c);
char		**ft_strtbdup(char **tb);
char		*ft_getenv(char **tb, char *str);
void		ft_unset(char **arg, char ***env);
void		ft_export(char **arg, char ***env);

/*
** exec
*/

void		tmp_sh(t_shell *tmp, t_shell *sh, int index, int is_sub);
int			redi(t_shell *sh, t_redi *redi);
int			wait_exec(t_shell *sh, char **cli);
int			sort_comm(t_shell *sh);
void		epur_tb(t_com *com, int len);

int			exe(t_shell *sh, char *comm, char **argv);
int			search_exec(t_shell *sh, char *comm, char **argv);
int			exec_cli(t_shell *sh, t_com *inter);
int			exec_redi(t_shell *sh, t_redi *tmp);

void		ft_fatal(char *str);
void		shift_com(t_shell *sh, int fail);

char		*conv_esc(char *str);
char		*set_esc(char *str);
int			ft_strlento_comm(char *str, char *to_find);
char		*enclosed(char *str, char c);

/*
** redirections
*/

void		set_redi_path(t_redi *redi);
int			exec_pipe(t_shell *sh, char *comm, char **argv);
void		reset_std(t_shell *sh, t_com *com, t_redi *redi);

int			safe_dup(int fd1, int fd2, int *pipe);
void		arg_replace(t_shell *sh, char **arg);
int			write_env(char **env);

/*
** substitute functions
*/

int			br_util(char *str);
int			skip_br(char *str, int i);
int			check_bracket(char *str);
int			skip_bracket(char *str);
void		add_comm(t_com *com, char *str);
void		replace_in(t_shell *sh, t_com *com);
int			local_env(char **tmp, char *todel);
void		replace_local(t_shell *sh, char **str, int i, int ret);
char		**ft_custom_split(char *s, char **tb, int op);
int			bracket(char *str, char *brack);
void		sub_ar(t_shell *sh, char **arg, int i);
void		get_sub(t_shell *sh);
void		comm_substitute(t_shell *sh, char **str, int i);

/*
** glob_functions
*/

int			is_special(char **str, char **to_match);
int			ft_match(char *str, char *to_match);
t_glob		*ft_glob(char *regstr, int opt);
void		free_globs(t_glob *glob);
void		true_sort(t_paths *begin, t_paths *to_add);

t_paths		*path_is_valid(char *path, char *name,
		t_dirent *dire, char **regex);
t_paths		*end_sort(t_paths *tmp, char *str, char **regex);
t_paths		*files_queue(char *str, DIR *dir, char **regex);
t_paths		*recc(char *str, char **regex);

/*
** hash_functions
*/

void		ft_unalias(char **arg, char ***env);
t_btree		**alias_tb(void);
void		ft_alias(char **arg, char ***env);
void		alias_file(t_shell *sh);

void		ft_free_hash(t_btree **tb, size_t size);
char		*ft_get_hash(t_btree **hash_tb, char *key);
int			ft_set_hash(t_btree **begin, char *key, char *value);
size_t		hash(char *str);
int			ft_hashcmp(void *content, void *content2);
void		btree_erase(t_btree **root, void *erase(void **));
void		erase_hash_tab(t_btree **hash_tb);
void		*erasehash(void **item);
#endif
