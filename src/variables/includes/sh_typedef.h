/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_typedef.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 12:04:19 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/10 11:39:11 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_TYPEDEF_H
# define SH_TYPEDEF_H
# include "sh_include.h"

typedef struct termios		t_termios;
typedef struct dirent		t_dirent;
typedef struct s_glob		t_glob;
typedef struct stat			t_stat;
typedef struct timespec		t_timespec;
typedef struct sigevent		t_sigevent;
//typedef struct itimerspec	t_timer;
typedef struct itimerval	t_timer;

typedef struct	s_read
{
	char		delim;
	char		**variables;
	int			deep;
	char		*readline;
	int			readline_active;
	size_t		nchars;
	size_t		nchars_exact;
	char		*prompt;
	int			bl_active;
	int			echo;
	t_timespec	timer;
	int			fd;
	int			error;
}				t_read;

typedef struct	s_variable
{
	int		deep;
	char	*name;
	char	*str;
	t_list	*array;
	int		deported;
}				t_variable;

typedef struct	s_variable_array
{
	char	*str;
	int		index;
}				t_variable_array;

typedef struct	s_direction
{
	int		in;
	char	*out_file;
	char	*in_string;
	int		out_fd;
	int		out_type;
}				t_direction;

typedef struct	s_command
{
	t_list	*direction;
	char	*line;
	int		separator;
}				t_command;

typedef struct	s_corr
{
	int	x;
	int	y;
}				t_corr;

typedef struct	s_tb
{
	t_glob		*glob;
	char		*str;
	struct s_tb	*next;
}				t_tb;

typedef struct	s_redi
{
	char			*path;
	int				type;
	int				fd[2];
	struct s_redi	*next;
}				t_redi;

typedef struct	s_com
{
	char			**cli;
	int				pipe[2];
	int				len;
	int				type;
	t_tb			*tb;
	t_redi			*redi;
	bool			tmp;
	struct s_com	*next;
}				t_com;

typedef struct	s_parser
{
	char			*comm;
	char			op[3];
	char			type;
	int				wait;
	int				drop;
	struct s_parser	*next;
}				t_parser;

typedef struct	s_substitute
{
	bool	is_sub;
	int		pipe[2];
	size_t	size;
	t_list	*begin;
}				t_sub;

typedef struct	s_hash
{
	char	*key;
	char	*value;
}				t_hash;

typedef struct	s_shell
{
	void		(*f_built[7])(char **av, char ***argv);
	t_btree		**hash_tb;
	int			std[3];
	char		*here_doc;
	char		**env;
	t_com		*begin;
	t_com		*com;
	t_sub		sub;
}				t_shell;

typedef struct	s_paths
{
	char			is_dir;
	char			*path;
	char			*name;
	struct s_paths	*next;
}				t_paths;

struct			s_glob
{
	int				nb_paths;
	t_paths			*paths;
};

typedef struct	s_line
{
	char		*eof;
	int			size_eof;
	char		*line;
	int			size_line;
	t_parser	*parser;
	int			parser_nb;
}				t_line;
#endif
