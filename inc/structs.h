/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:16:56 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/12 14:56:08 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"

// TOKENS
typedef struct s_token
{
	char			*value;
	int				type;
	int				var_stop;
	int				*qts_stop;
	int				idx;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_redir
{
	int			redir_in;
	int			redir_out;
	int			append_in;
	int			append_out;
	char		*infile;
	char		*outfile;
	char		*delimiter;
}				t_redir;

// COMMANDS
typedef struct s_cmd
{
	int				fd_in;
	int				fd_out;
	int				pipe[2];
	int				builtin;
	char			*cmd;
	char			**cmd_args;
	char			**args;
	t_redir			*redir;
}				t_cmd;

// CMD LIST
typedef struct s_cmdlst
{
	int					type;
	t_cmd				*cmd;
	struct s_cmdlst		*next;
	struct s_cmdlst		*prev;
}				t_cmdlst;

// TERMINAL -- termios
typedef struct s_terminal
{
	struct termios	dftl;
	struct termios	new;
}				t_terminal;

// SHELL -- minishell data
typedef struct s_shell
{
	char		**env;
	char		*input;
}				t_shell;

// GLOBAL (variable)
typedef struct s_data
{
	int				err;
	t_shell			shell;
	t_terminal		terminal;
	t_cmdlst		*cmds;
	t_token			*tokens;
}				t_data;

typedef struct s_global
{
	t_data	*data;
}			t_global;

#endif
