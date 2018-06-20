/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_define.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 12:08:50 by tcharrie          #+#    #+#             */
/*   Updated: 2018/06/20 15:05:12 by tcharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_DEFINE_H
# define SH_DEFINE_H

# define LOGFILE "/tmp/.sh_errorlog"
# define HISTORYFILE "~/.sh_history"
# define ENVFILE "/tmp/.sh_env"

# define TERN "ERREUR DE TERN SYNTAX"
# define HASH_SIZE 1000
# define BUFFSIZE 100
# define ERR -1
# define ERR_PARS1_MSG "21sh: syntax error near unexpected token '|'\n"
# define ERR_PARS2_MSG "21sh: syntax error near unexpected token '&'\n"
# define ENVFAILED "Failed to get the environment\n"
# define MALLOC_ERR '\00'
# define MALLOC_ERR_MSG "21sh: An error occured while using malloc\n"
# define NO_CHAR_MSG "21sh: Starting without insert character mode\n"
# define NO_NEWLINE_MSG "21sh: Starting without insert line mode\n"
# define NO_DELLINE_MSG "21sh: Starting without del line mode\n"
# define PARSING_ERROR_3 '\04'
# define PARSING_ERROR_3_MSG "21sh: syntax error near unexpected token '<'\n"
# define PARSING_ERROR_4 '\05'
# define PARSING_ERROR_4_MSG "21sh: syntax error near unexpected token '>'\n"
# define PARSING_ERROR_5 '\06'
# define SIGNAL_ERR_MSG "21sh: Failed to setup the catch for signals, exiting"

# define CODE_RESET 0
# define CODE_SET 1
# define CODE_GET 2
# define CODE_PUSH 3

# define ESC "\a\b\f\n\r\t\v\\"
# define QUOTES "`\"\'"
# define HD (char *[14]){"||", "&&", "|", "&", ";", ">>", "<<", ">&", "<&", " "}
# define NORM (char *[14]){" ", "<", ">"}
# define SEP (char *[7]){"||", "&&", "|", "&", ";", "\n"}
# define M_SEP (char *[6]){"||", "&&", "|"}
# define REDI (char *[7]){"<<", ">>", "<&",">&", "<", ">"}
# define UNESC "0xabfnrtv\\"
# define FBUILT (char *[10]){"echo", "env"}
# define BUILT (char *[10]){"cd", "setenv" ,"unsetenv", "alias", "unalias", "read", "unset", "export"}
# define GLOB "[*?"
# define ENDWORD " \n|;&<>"
# define ENDWORDVIS " \n;|&<>`'\"\\"
# define SPECIALCHAR "`\"'\\!$&|?<>* \n"

# define KEY_LEFT "\33[D"
# define KEY_LEFT_SHIFTED "\33[1;2D"
# define KEY_RIGHT "\33[C"
# define KEY_RIGHT_SHIFTED "\33[1;2C"
# define KEY_UP "\33[A"
# define KEY_UP_SHITED "\33[1;2A"
# define KEY_DOWN "\33[B"
# define KEY_DOWN_SHIFTED "\33[1;2B"
# define KEY_SELECT_LEFT "\33\133\61\73\66\104"
# define KEY_SELECT_RIGHT "\33\133\61\73\66\103"
# define KEY_SELECT_CPY tgetstr("F6", 0)
# define KEY_SELECT_PASTE tgetstr("F7", 0)
# define KEY_END "\33[F"
# define KEY_END_SHIFTED "\33[1;2F"
# define KEY_HOME "\33[H"
# define KEY_HOME_SHIFTED "\33[1;2H"
# define KEY_DELETE tgetstr("kD", 0)
# define KEY_ERASE "\177"
# define NEWLINE "\n"
# define KEY_COMPLETION "\t"

# define CODE_ENVGET '\01'
# define CODE_ENVADD '\02'

# define COMPLETION_FILE 1
# define COMPLETION_COM 2

# define VAR_LIM "~`!@#$%^&*()-+={}[]|;'\"?></.,\\$ "
# define VAR_LIM2 "~`!@#$%^&*()-+=[]|;'\"?></.,\\$} "

#endif
