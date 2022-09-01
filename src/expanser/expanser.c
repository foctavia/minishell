/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:13:33 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/30 15:17:44 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_expanser(t_token **tokens)
{
	int			res;
	t_token		*tmp;

	res = 0;
	tmp = *tokens;
	while (tmp && !g_global.data->err)
	{
		if (tmp->type == DBL_QUOTE && !ft_tabint(tmp->qts_stop, -1))
		{
			res = expanse_quote(tmp, tmp->value, tmp->idx++);
		}
		tmp = tmp->next;
	}
	tmp = *tokens;
	while (tmp)
	{
		if (tmp->type == DBL_QUOTE && !ft_tabint(tmp->qts_stop, -1))
			res = quote_expanser(tokens);
		tmp = tmp->next;
	}
	return (res);
}

int	ms_expanser(t_token **tokens)
{
	if (!var_expanser(tokens))
	{
		printf("after var_expenser\n");
		display_tokens();
		printf("_________________________________________________________\n\n");
		if (!quote_expanser(tokens))
		{
			printf("after quote_expanser\n");
			display_tokens();
			printf("_________________________________________________________\n\n");
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}

// int	ms_expanser(t_token **tokens)
// {
// 	static int	idx;
// 	int			res;
// 	t_token		*tmp;

// 	res = 0;
// 	tmp = *tokens;
// 	while (tmp && !g_global.data->err)
// 	{
// 		if (tmp->type == VAR)
// 			res = expanse_var(&tmp);
// 		else if (tmp->type == DBL_QUOTE)
// 			res = expanse_quote(tmp, tmp->value, idx++);
// 		if (!tmp)
// 			break ;
// 		tmp = tmp->next;
// 	}
// 	tmp = *tokens;
// 	while (tmp)
// 	{
// 		if ((tmp->type == DBL_QUOTE && !ft_tabint(tmp->qts, -1)) \
// 			|| (tmp->type == VAR && tmp->var > -1))
// 			res = ms_expanser(tokens);
// 		tmp = tmp->next;
// 	}
// 	return (res);
// }

