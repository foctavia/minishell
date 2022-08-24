/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:01:32 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/24 15:18:56 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

// SYSTEM LIBRARIES
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>
# include <string.h>

// MS LIBRARIES
# include "structs.h"
# include "defines.h"

// global

extern t_global g_global; 

/*
**
** INIT
**
*/
int	ms_init(t_data *data, char **argv, char **env);
/*
**
** LEXER
**
*/
int	ms_lexer(char *str, t_token **tokens);
int	tokenize(t_token **tokens, char *str, int *i, int type);
int	is_isspace(char c);
int	is_quote(char *str, int *type);
int	is_oper(char c1, char c2, int *type);
int	is_special(char c, int *type);
char	*copy_chars(char *str, int *i, int n);
char	*copy_word(char *str, int *i);
char	*copy_quote(char *str, int *i);
/*
**
** LEXER
**
*/
int	ms_expanser(t_token **token);
/*
**
** CLEAN
**
*/
void	clean(t_data *data);
/*
**
** UTILS
**
*/
void	display_tokens();
int		err_msg(int	err, char c);

#endif