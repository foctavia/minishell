/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:35:56 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/09 22:56:01 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_builtin(t_cmdlst **cmds, t_env *env)
{
	if ((*cmds)->cmd->builtin == BD_EXIT)
		ms_exit((*cmds)->cmd->cmd, &(*cmds)->cmd->args[1], env);
	else if ((*cmds)->cmd->builtin == BD_ENV)
		ms_env((*cmds)->cmd->cmd, &(*cmds)->cmd->args[1], env);
	else if ((*cmds)->cmd->builtin == BD_EXPORT)
		ms_export((*cmds)->cmd->cmd, &(*cmds)->cmd->args[1], env);
	return (EXIT_SUCCESS);
}

char	**free_str(char **str, int i)
{
	while (i >= 0)
		free(str[i--]);
	free(str);
	err_msg(-2, 0);
	return (NULL);
}

char	**tab_env(t_env *env)
{
	t_env	*tmp;
	char	**new;
	int		i;
	
	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	new = malloc(sizeof(char *) * (tmp->i + 1));
	if (!new)
	{
		err_msg(-2, 0);
		return (NULL);
	}
	i = 0;
	tmp = env;
	while(tmp)
	{
		new[i] = malloc(sizeof(char) * (ft_strlen(tmp->val) + 1));
		if (!new[i])
			return (free_str(new, i));
		new[i] = ft_strncpy(new[i], tmp->val, ft_strlen(tmp->val));
		tmp = tmp->next;
		i++;
	}
	new[i] = NULL;
	return (new);
}

int	ms_execve(t_cmdlst **cmds, t_env *env)
{
	pid_t	pid;
	int		pipes[2];
	char	**tmp_env;

	tmp_env = tab_env(env);
	pipe(pipes);
	pid = fork();
	if (pid == -1)
		exit(errno);
	if (pid == 0)
	{
		dup2(pipes[0], STDIN_FILENO);
		dup2(STDOUT_FILENO, pipes[1]);
		if (execve((*cmds)->cmd->cmd, (*cmds)->cmd->args, tmp_env) < 0)
			exit(errno);
	}
	waitpid(pid, NULL, 0);
	free_tab(tmp_env);
	return (EXIT_SUCCESS);
}

int	ms_execute(t_cmdlst **cmds, t_env *env)
{
	if ((*cmds)->cmd->builtin)
		ms_builtin(cmds, env);
	else
		ms_execve(cmds, env);
	return (EXIT_SUCCESS);
}
