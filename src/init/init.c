/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:14:01 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/23 17:59:18 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_init(t_data *data, int argc, char **argv, char **env)
{
	(void)argv;
	(void)argc;
	(void)env;
	memset(data, 0, sizeof(t_data));
	g_global.data = data;
	return (EXIT_SUCCESS);
}

