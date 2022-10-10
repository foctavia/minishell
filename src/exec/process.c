/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:47:30 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/10 09:50:37 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_cmd *cmd, char **env)
{
	int	res;

	res = EXIT_SUCCESS;
	if (cmd->builtin == BD_EXIT)
		res = ms_exit(cmd->cmd, &cmd->args[1], env);
	else if (cmd->builtin == BD_CD)
		res = ms_cd(cmd->cmd, cmd->args, env);
	else if (cmd->builtin == BD_EXPORT)
		res = ms_export(cmd->cmd, &cmd->args[1], env);
	else if (cmd->builtin == BD_UNSET)
		res = ms_unset(cmd->cmd, &cmd->args[1], env);	
	else if (cmd->builtin == BD_ENV)
		res = ms_env(cmd->cmd, &cmd->args[1], env);
	else if (cmd->builtin == BD_PWD)
		exit(ms_pwd(cmd->cmd, cmd->args, env));
	else if (cmd->builtin == BD_ECHO)
		exit(ms_echo(cmd->cmd, cmd->args));
	return (res);
}

int	exec_child(t_cmd *cmd, char **env)
{
	redir_fd(cmd);
	if (cmd->builtin)
		return (exec_builtin(cmd, env));
	if (execve(cmd->cmd, cmd->args, env) < 0)
		exit(errno);
	return (EXIT_SUCCESS);
}

int	wait_child(t_cmdlst *cmds)
{
	int	exit_status;
	int	error;

	error = 0;
	if (cmds->type == WORD)
	{
		waitpid(cmds->cmd->pid, &exit_status, 0);
		if (WIFEXITED(exit_status))
			error = WEXITSTATUS(exit_status);
		if (error)
			return (error);
	}
	else
	{
		waitpid(cmds->prev->cmd->pid, &exit_status, 0);
		return (wait_child(cmds->next));
	}
	return (EXIT_SUCCESS);
}

int	exec_cmd(t_cmdlst *cmds, char **env)
{
	t_cmd	*cmd;
	int		res;

	res = EXIT_SUCCESS;
	cmd = cmds->cmd;
	if (!cmd->cmd && !cmd->redir)
		exit(127);
	if (!cmd->cmd)
		exit(0);
	if (cmd->builtin && (cmd->builtin == BD_CD || cmd->builtin == BD_EXPORT
		|| cmd->builtin == BD_UNSET || cmd->builtin == BD_EXIT
		|| cmd->builtin == BD_ENV))
		return (exec_builtin(cmd, env));
	cmd->pid = fork();
	if (cmd->pid == -1)
		exit(errno);
	if (cmd->pid == PID_CHILD)
		res = exec_child(cmd, env);
	res = wait_child(cmds);
	return (res);
}

int	exec_pipe(t_cmdlst *cmds, char **env)
{
	int		fd[2];
	int		pipes;
	t_cmd	*next;
	t_cmd	*prev;
	
	prev = cmds->prev->cmd;
	next = cmds->next->cmd;
	pipes = pipe(fd);
	if (pipes == -1)
		exit(errno);
	prev->pid = fork();
	if (prev->pid == -1)
		exit(errno);
	if (prev->fd_out != -1)
		prev->fd_out = fd[P_WRITE];
	if (prev->pid == PID_CHILD)
	{
		close(fd[P_READ]);
		return (exec_child(prev, env));
	}
	close(fd[P_WRITE]);
	close_fd(prev);
	if (next->fd_in != -1)
		next->fd_in = fd[P_READ];
	return (ms_execute(cmds->next, env));
	
}
