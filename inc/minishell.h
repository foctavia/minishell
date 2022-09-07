/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:01:32 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/07 18:52:13 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// SYSTEM LIBRARIES
# include <stdio.h>
// #include "/usr/include/readline/readline.h"
// #include "/usr/include/readline/history.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>
# include <string.h>
# include <curses.h>
# include <term.h>

// MS LIBRARIES
# include "structs.h"
# include "defines.h"

// global

extern t_global	g_global;

/*
**
** INIT
**
*/
int		ms_init(t_data *data, char **argv, char **env);
/*
**
** LEXER
**
*/
int		ms_lexer(char *str, t_token **tokens);
int		tokenize(t_token **tokens, char *str, int *i, int type);
int		quote_init(t_token *tokens);
int		lexer_checker(t_token *head);
int		is_delimiter(char *str);
int		is_isspace(char c);
int		is_quote(char *str, int *type);
int		is_oper(char c1, char c2, int *type);
int		is_special(char *str, int *type);
int		lexer_checker(t_token *head);
void	add_token(t_token *new, t_token **tokens);
char	*copy_chars(char *str, int *i, int n);
char	*copy_word(char *str, int *i);
char	*copy_var(char *str, int *i);
char	*copy_quote(char *str, int *i);
/*
**
** EXPANSER
**
*/
int		ms_expanser(t_token **token);
int		expanse_var(t_token **tokens);
int		expanse_quote(t_token *tokens, char *str, int idx);
int		delete_quote(t_token **tokens);
void	insert_token(t_token **tokens, t_token *new);
/*
**
** PARSER
**
*/
int 		ms_parser(t_token *tokens, t_cmdlst **cmds);
t_cmd		*create_cmd(t_token **token);
t_redir		*create_redir(void);
t_cmdlst	*create_cmdlst(int type, t_cmd *cmd);
void		add_cmdlst(t_cmdlst **lst, t_cmdlst	*new);
int			cmd_addredir(t_token **token, t_cmd *cmd);
char		*get_cmdpath(char *cmd);
int			is_delim(t_token *token);
int			is_redir(t_token *token);
/*
**
** CLEAN
**
*/
void	clean(t_data *data);
void	free_tokens(t_token **tokens);
void	free_tab(char **table);
/*
**
** UTILS
**
*/
int		get_tablen(char **table);
int		*ft_tabint(int *t, int c);
int		ft_isdigit(char c);
int		ft_strcmp(char *s1, char *s2);
char	**ft_split(char *s, char c);
int		ft_strncmp(char *s1, char *s2, int n);
int		ft_strlen(char *str);
int		err_msg(int err, char c);
char	*err_msg_str(int code, char *str);
char	*ft_strjoin(char *s1, char *s2, int clean);
char	*ft_strncpy(char *dst, char *src, int n);
void	display_tokens(void);
void	display_cmds(void);
void	display_specific_tokens(t_token *head);
/*
**
** BUILTINS
**
*/
int		ms_exit(char *cmd, char **args);

#endif