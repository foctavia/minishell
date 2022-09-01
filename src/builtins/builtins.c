/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:56:16 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/25 19:02:37 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_buildin(char *cmd)
{
	if (!ft_strcmp("echo", cmd))
		return (BD_ECHO);
	else if (!ft_strcmp("cd", cmd))
		return (BD_EXIT);
	else if (!ft_strcmp("pwd", cmd))
		return (BD_EXIT);
	else if (!ft_strcmp("export", cmd))
		return (BD_EXIT);
	else if (!ft_strcmp("unset", cmd))
		return (BD_EXIT);
	else if (!ft_strcmp("env", cmd))
		return (BD_EXIT);
	else if (!ft_strcmp("exit", cmd))
		return (BD_EXIT);
	else
		return (EXIT_FAILURE);		
}