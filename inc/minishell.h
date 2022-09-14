/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:01:32 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/14 22:28:05 by foctavia         ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <errno.h>

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
int		copy_env(t_data *data, char **env);
/*
**
** LEXER
**
*/
int		ms_lexer(char *str, t_token **tokens);
int		tokenize(t_token **tokens, char *str, int *i, int type);
int		lexer_checker(t_token *head);
int		is_delimiter(char *str);
int		is_delimiter_spc(char *str);
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
int		expanse_quote(t_token *tokens, char *str);
int		delete_quote(t_token **tokens);
void	insert_token(t_token **tokens, t_token *new);
/*
**
** PARSER
**
*/
int 		ms_parser(t_token *tokens, t_cmdlst **cmds);
int			cmd_addredir(t_token **token, t_cmd *cmd);
int			is_delim(t_token *token);
int			is_redir(t_token *token);
int			ft_strtoken(char *str);
int			read_file(char *file);
int			read_stdin(char *delimiter);
int			create_file(char *file);
int			append_file(char *file);
void		add_cmdlst(t_cmdlst **lst, t_cmdlst	*new);
void		cmd_setargs(t_token **token, t_cmd *new);
char		*copy_cmd(t_token **token);
char		*get_cmdpath(char *cmd);
t_cmd		*create_cmd(t_token **token);
t_cmd		*init_cmd(void);
t_redir		*create_redir(void);
t_cmdlst	*create_cmdlst(int type, t_cmd *cmd);
/*
**
** EXEC
**
*/
int			ms_execute(t_cmdlst **cmds, char **env);
int			ms_wait(t_cmdlst **cmds);
int			exec_cmd(t_cmdlst **cmds, char **env);
int			set_fd(t_cmdlst **cmds);
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
int 	is_alnum(char c);
int		is_alpha(char c);
int		ft_tablen(char **table);
int		ft_isdigit(char c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int n);
int		ft_strlen(char *str);
int		err_msg(int err, char c);
int		err_msg_1(int code, char c);
int		err_bd(int code, char *func, char *arg);
char	*get_next_line(int fd);
char	*err_msg_str(int code, char *str);
char	*ft_getenv(char *name);
char	*ft_strchr(char *str, int c);
char	*ft_strstr(char *str, char *to_find);
char	*ft_strjoin(char *s1, char *s2, int clean);
char	*ft_strncpy(char *dst, char *src, int n);
char	**ft_split(char *s, char c);
void	display_tokens(void);
void	display_cmds(void);
void	display_specific_tokens(t_token *head);
/*
**
** BUILTINS
**
*/
int		ms_cd(char *cmd, char **args, char **env);
int		ms_echo(char *cmd, char **args);
int		ms_exit(char *cmd, char **args, char **env);
int		ms_env(char *cmd, char **args, char ** env);
int		ms_export(char *cmd, char **args, char **env);
int		ms_unset(char *cmd, char **args, char **env);
int		display_export(char **env);
void	display_env(char **env);

#endif