/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:13:33 by foctavia          #+#    #+#             */
/*   Updated: 2022/09/01 14:27:36 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_expanser(t_token **token)
{
	int		res;
	t_token	*tmp;

	res = 0;
	tmp = *token;
	while (tmp && !g_global.data->err)
	{
		if (tmp->type == VAR)
			expanse_var(&tmp);
		tmp = tmp->next;
	}
	return (res);
}
