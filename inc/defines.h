/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:22:28 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/25 19:01:08 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_DEFINES_H
#define MS_DEFINES_H

# define ERROR_LEXER -1

// Colours
# define RED "\033[1;31m"
# define ORANGE	"\e[38;5;166m"
# define GREEN "\033[1;32m"
# define RESET "\033[m"
# define LRED "\033[1;31m"
# define LGREEN	"\033[1;32m"
# define LYELLOW	"\033[1;33m"
# define YELLOW	"\033[0;33m"
# define BLUE "\033[0;34m"
# define LBLUE "\033[1;34m"
# define PURPLE	"\033[0;35m"
# define LPURPLE "\033[1;35m"
# define CYAN "\033[0;36m"
# define LCYAN "\033[1;36m"
# define LGREY "\033[0;37m"
# define WHITE "\033[1;37m"
# define PINK "\e[38;5;205m"
# define LPINK "\e[38;4;200m"

// Generic
# define PROMPT RED"m"LRED"i"LYELLOW"n"YELLOW"i"LGREEN"s"GREEN"h"LBLUE"e"LPINK"l"LPURPLE"l"RESET"$ "

// Tokens type
# define WORD 1
# define PIPE 2
# define REDIR_IN 3
# define REDIR_OUT 4
# define OPEN_BRK 5
# define CLOSE_BRK 6
# define DBL_QUOTE 7
# define SGL_QUOTE 8
# define VAR 9
# define OPERAND 10
# define OPEROR 11
# define APPEND_IN 12
# define APPEND_OUT 13

// Chars decimal value
# define DQUOTE 34
# define SQUOTE 39

// BUILTINS
# define BD_ECHO 101
# define BD_CD 102
# define BD_PWD 103
# define BD_EXPORT 104
# define BD_UNSET 105
# define BD_ENV 106
# define BD_EXIT 107

#endif