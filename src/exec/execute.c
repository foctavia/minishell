/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:35:56 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/10 12:17:58 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_execute(t_cmdlst *cmds, char **env)
{
	int	res;

	res = EXIT_SUCCESS;
	if (!cmds)
		return (res);
	if (!env)
		return (EXIT_FAILURE);
	display_cmds();
	if (cmds->type == WORD)
	{
		printf("in ms_execute with a cmd: %s\n", cmds->cmd->cmd);
		res = exec_cmd(cmds, env);
		close_fd(cmds->cmd);
	}
	if (cmds->type == PIPE)
	{
		printf("in ms_execute with a pipe\n");
		res = exec_pipe(cmds, env);
	}
	return (res);
}
