/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:35:56 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/10 09:47:59 by owalsh           ###   ########.fr       */
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
	if (cmds->type == WORD)
	{
		res = exec_cmd(cmds, env);
		close_fd(cmds->cmd);
	}
	else if (cmds->type == PIPE)
		res = exec_pipe(cmds, env);
	return (res);
}
