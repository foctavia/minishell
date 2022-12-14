/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:13:13 by foctavia          #+#    #+#             */
/*   Updated: 2022/10/11 16:05:28 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expanse_tilde(t_token **token)
{
	char	*val;

	if ((*token)->value && (*token)->value[0] && !(*token)->value[1])
	{
		val = (*token)->value;
		free(val);
		(*token)->value = ft_getenv("HOME");
		if (!(*token)->value)
		{
			delete_token(token);
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_SUCCESS);
}
