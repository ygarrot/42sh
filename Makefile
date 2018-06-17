# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/11 13:13:35 by ygarrot           #+#    #+#              #
#    Updated: 2018/06/17 16:23:14 by ygarrot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

FLAGS =  -Wall -Werror -Wextra -g3 #-fsanitize=address,undefined

SRC_FOLDER = src/

SRC_FP = \
		  main.c \

SRC_FP += \
		  builtin/ft_cd.c \
		  builtin/ft_echo.c \
		  builtin/ft_env.c \
		  builtin/ft_exit.c \
		  builtin/ft_setenv.c \
		  builtin/ft_strtabdup.c \
		  builtin/ft_unsetenv.c \
		  builtin/ft_unalias.c \
		  builtin/ft_alias.c \
		  builtin/ft_export.c \
		  builtin/ft_unset.c

SRC_FP += \
		completion/ft_completion.c \
		completion/ft_completion_com.c \
		completion/ft_completion_file.c \
		completion/ft_completion_save.c \
		completion/ft_completion_start.c \
		completion/ft_completion_startpos.c \
		completion/ft_completionstr.c \
		completion/ft_completion_type.c \
		completion/ft_getdir.c

SRC_FP +=\
		variables/ft_variable.c \
		variables/ft_variable_create.c \
		variables/ft_variable_misc.c \
		variables/ft_variable_pars.c \
		variables/ft_variable_add.c \
		variables/ft_variable_builtin.c

SRC_FP += \
		  env/ft_storeenv.c

SRC_FP += \
		  exec/exec.c \
		  exec/replace_in.c \
		  exec/redirect.c

SRC_FP += \
		  glob/dir_tour.c \
		  glob/globbing.c

SRC_FP += \
		  hash/btree_erase.c \
		  hash/ft_hashcmp.c \
		  hash/ft_hash.c

SRC_FP += \
		  history/ft_history.c \
		  history/ft_history_parser.c \
		  history/ft_historymove.c 

SRC_FP += \
		  initialisation/ft_initenv.c \
		  initialisation/ft_signal.c \
		  initialisation/ft_terminal.c \
		  initialisation/init.c \
		  initialisation/ft_initialisation.c

SRC_FP += \
		  misc/erase.c \
		  misc/ft_error.c \
		  misc/ft_memory.c \
		  misc/ft_print.c \
		  misc/ft_separator.c \
		  misc/ft_parserpushback.c \
		  misc/ft_opendir.c

SRC_FP += \
		  parser/ins_do_op.c \
		  parser/interpreter.c \
		  parser/lexer.c \
		  parser/arg_replace.c \
		  parser/parser.c

SRC_FP += \
		  read/ft_read.c \
		  read/ft_read_assign.c \
		  read/ft_read_error.c \
		  read/ft_read_init.c \
		  read/ft_read_initterminal.c \
		  read/ft_read_move.c \
		  read/ft_read_move_b.c \
		  read/ft_read_move_c.c \
		  read/ft_read_parser.c \
		  read/ft_read_parser_assign.c \
		  read/ft_read_parser_assignn.c \
		  read/ft_read_parser_assignnn.c \
		  read/ft_read_recover.c \
		  read/ft_read_recover_insert.c \
		  read/ft_read_split.c \
		  read/ft_read_timer.c \

SRC_FP += \
		  screen/ft_getpos.c \
		  screen/ft_goto.c \
		  screen/ft_lenchar.c \
		  screen/ft_lenline.c \
		  screen/ft_lenline.c \
		  screen/ft_lenword.c \
		  screen/ft_move_all.c \
		  screen/ft_move_base.c \
		  screen/ft_move_base_.c \
		  screen/ft_move_bonus.c \
		  screen/ft_scroll.c \
		  screen/ft_readtopattern.c

SRC_FP += \
		  signal/error_op.c \
		  signal/error_handling.c \
		  signal/ft_sigint.c

SRC_FP += \
		  static/ft_subshell.c

SRC_FP += \
		  user/ft_getentry.c \
		  user/ft_heredoc.c \
		  user/ft_read.c \
		  user/ft_read_newline.c \
		  user/ft_specialchar.c

SRC_FP += \
		  utils/parse_utils.c \
		  utils/ft_find_and_replace.c \
		  utils/glob_utils.c \
		  utils/ft_strsplit_comm.c \
		  utils/exec_utils.c \
		  utils/list_tools.c \
		  utils/replace_utils.c \
		  utils/replace_backslashn.c

SRC_FP += \
		  write/ft_erase.c \
		  write/ft_insert.c \
		  write/ft_lentoend.c \
		  write/ft_printchar.c \
		  write/ft_printstr.c \
		  write/ft_select.c \
		  write/ft_select_reset.c

SRC_FP += \
		 do_op/do_op.c \
		 do_op/do_list.c \
		 do_op/increment.c \
		 do_op/exe_op.c \
		 do_op/ft_bitwise.c \
		 do_op/ft_comp.c \
		 do_op/ft_split_custom.c \
		 do_op/logic_op.c \
		 do_op/op.c \
		 do_op/parse_op.c \
		 do_op/free_do.c \
		 do_op/skip_char.c

#Colors
_RED=\x1b[31m
_GREEN=\x1b[32m
_BLUE=\x1b[94m
_WHITE=\x1b[37m
_END=\x1b[0m

SRC = $(addprefix $(SRC_FOLDER), $(SRC_FP))

INCLUDE =  includes/

LIBFT = libft/libft.a

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	@gcc $(FLAGS) -o $@ -c $< -I $(INCLUDE)
	@printf "                                                        \r"
	@printf " $(_BLUE)Compiling $@$(_END)\r"

$(NAME): $(OBJ)
	@printf "                                                        \r"
	@make -C libft -j
	@gcc $(FLAGS) -o $(NAME) $^ -L libft -l ft -ltermcap
	@printf "                                                        \r"
	@printf "21sh built\n"

test: all clean

clean:
	@rm -f $(OBJ)
	@make -C libft clean

fclean:
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
