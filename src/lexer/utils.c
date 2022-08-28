/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:19:11 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/28 20:49:16 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	is_quote(char *str, int *type)
{
	int	i;
	int	count;

	i = 0;
	if (str[0] != DQUOTE && str[0] != SQUOTE)
		return (0);
	i++;
	count = 1;
	while (str && str[i])
	{
		if (str[i] == str[0])
			count++;
		i++;
	}
	if (!(count % 2))
	{
		if (str[0] == 34)
			*type = DBL_QUOTE;
		else if (str[0] == 39)
			*type = SGL_QUOTE;
		return (1);
	}
	err_msg(-1, str[0]);
	return (0);
}

int	is_oper(char c1, char c2, int *type)
{
	if (c1 != c2)
		return (0);
	if (c1 == '&')
		*type = OPERAND;
	else if (c1 == '|')
		*type = OPEROR;
	else if (c1 == '<')
		*type = APPEND_IN;
	else if (c1 == '>')
		*type = APPEND_OUT;
	else
		return (0);
	return (1);
}

int	is_special(char c, int *type)
{
	if (c == '|')
		*type = PIPE;
	else if (c == '<')
		*type = REDIR_IN;
	else if (c == '>')
		*type = REDIR_OUT;
	else if (c == '$')
		*type = VAR;
	else if (c == '(')
		*type = OPEN_BRK;
	else if (c == ')')
		*type = CLOSE_BRK;
	else
		return (0);
	return (1);
}
