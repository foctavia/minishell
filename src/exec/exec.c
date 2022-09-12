/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:35:56 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/12 16:45:37 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_builtin(t_cmd *cmd, char **env)
{
	if (cmd->builtin == BD_EXIT)
		ms_exit(cmd->cmd, &cmd->args[1], env);
	else if (cmd->builtin == BD_ENV)
		ms_env(cmd->cmd, &cmd->args[1], env);
	else if (cmd->builtin == BD_ECHO)
		ms_echo(cmd->cmd, cmd->args);
	else if (cmd->builtin == BD_CD)
		ms_cd(cmd->cmd, cmd->args);
	else if (cmd->builtin == BD_EXPORT)
		ms_export(cmd->cmd, &cmd->args[1], env);
	return (EXIT_SUCCESS);
}

int	ms_wait(t_cmdlst **cmds)
{
	int		error;
	int		exit_status;

	while (*cmds)
	{
		if ((*cmds)->cmd)
		{
			error = 0;
			waitpid((*cmds)->cmd->pid, &exit_status, 0);
			if (WIFEXITED(exit_status))
				error = WEXITSTATUS(exit_status);
			if (error)
			{
				write(2, strerror(error), ft_strlen(strerror(error)));
				write(2, "\n", 1);
				return (error);
			}
		}
		*cmds = (*cmds)->next;
	}
	return (EXIT_SUCCESS);
}

int	ms_dupwrite(t_cmd *cmd, t_cmd *next)
{
	if (cmd->redir)
	{
		if (cmd->redir->redir_out || cmd->redir->append_out)
		{
			dup2(cmd->fd_out, STDOUT_FILENO); // this is working
			close(cmd->fd_out);
		}
	}
	else if (next)
	{
		dup2(cmd->pipe[1], STDOUT_FILENO);
		close(cmd->pipe[1]);
	}
	return (EXIT_SUCCESS);
}

int	ms_dupread(t_cmd *cmd, t_cmd *prev)
{
	if (cmd->redir)
	{
		if (cmd->redir->redir_in || cmd->redir->append_in)
		{
			dup2(cmd->fd_in, STDIN_FILENO); // this is working
			close(cmd->fd_in);
		}
	}
	else if (prev)
	{
		dup2(prev->pipe[0], STDIN_FILENO);
		close(prev->pipe[0]);
	}
	// close(cmd->pipe[1]);
	return (EXIT_SUCCESS);
}

int	ms_execve(t_cmdlst **cmds, char **env)
{
	t_cmd	*prev;
	t_cmd	*next;
	t_cmd	*cmd;

	cmd = (*cmds)->cmd;
	prev = NULL;
	if ((*cmds)->prev && (*cmds)->prev->prev)
		prev = (*cmds)->prev->prev->cmd;
	next = NULL;
	if ((*cmds)->next && (*cmds)->next->next)
		next = (*cmds)->next->next->cmd;

	cmd->pid = fork();
	if (cmd->pid == -1)
		exit(errno);
	if (cmd->builtin == BD_EXIT)
		ms_exit(cmd->cmd, &cmd->args[1], env);
	if (cmd->pid == 0)
	{
		ms_dupread(cmd, prev);
		ms_dupwrite(cmd, next);
		if (cmd->builtin)
			exit(ms_builtin(cmd, env));
		if (execve(cmd->cmd, cmd->args, env) < 0)
			exit(errno);
	}
	else
	{
		if (cmd->fd_in)
			close(cmd->fd_in);
		if (cmd->fd_out)
			close(cmd->fd_out);
		if (prev && next)
		{
			close(prev->pipe[0]);
			close(cmd->pipe[1]);
		}
		else if (!next)
		{
			close(cmd->pipe[0]);
			close(cmd->pipe[1]);
		}
		else if (!prev)
			close(cmd->pipe[1]);
	}
	return (EXIT_SUCCESS);
}

int	ms_execute(t_cmdlst **cmds, char **env)
{
	t_cmdlst	*tmp;
	
	if (!env)
		return (EXIT_FAILURE);
	tmp = *cmds;
	while (tmp)
	{
		if (tmp->cmd)
		{
			if (pipe(tmp->cmd->pipe) == -1)
				exit(errno);
		}
		tmp = tmp->next;
	}
	tmp = *cmds;
	while (tmp)
	{
		if (tmp->cmd)
			ms_execve(&tmp, env);
		tmp = tmp->next;
	}
	return (ms_wait(cmds));
}
