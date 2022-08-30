/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:16:56 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/30 18:41:13 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifndef MS_STRUCTS_H
#define MS_STRUCTS_H

// TOKENS
typedef struct	s_token
{
	char			*value;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

// COMMANDS
typedef struct	s_cmd
{
	int				fd_in;
	int				fd_out;
	int				builtin;
	int				redir_in;
	int				redir_out;
	char			*cmd; // absolute path
	char			**args;
}				t_cmd;

// CMD LIST
typedef struct	s_cmdlst
{
	int 				type;
	t_cmd				*cmd;
	struct s_cmdlst		*next;
	struct s_cmdlst		*prev;
	
}				t_cmdlst;

// TERMINAL -- termios
typedef struct	s_terminal
{
	struct termios	dftl;
	struct termios	new;
}				t_terminal;


// SHELL -- minishell data
typedef struct	s_shell
{
	char		**env;
	char		*input;
	
}				t_shell;

// GLOBAL (variable)
typedef struct	s_data
{
	int				err;
	t_shell			shell;
	t_terminal		terminal;
	t_cmdlst		*cmds;		// linked list
	t_token			*tokens;	// linked list
}				t_data;

typedef struct	s_global
{
	t_data	*data;
	
}			t_global;

#endif