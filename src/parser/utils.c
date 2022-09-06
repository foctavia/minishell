/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:12:16 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/06 13:18:12 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(t_token *token)
{
	if (token->type == REDIR_IN || token->type == REDIR_OUT
		|| token->type == APPEND_IN || token->type == APPEND_OUT)
		return (1);
	return (0);
}

int	is_delim(t_token *token)
{
	if (token->type == PIPE || token->type == OPERAND || token->type == OPEROR)
		return (1);
	return (0);
}
