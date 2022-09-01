/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:08:26 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/28 20:15:43 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	insert_head(t_token *tokens, t_token *new)
{
	t_token	*tmp1;
	t_token	*tmp2;

	free(tokens->value);
	tokens->value = new->value;
	tokens->type = new->type;
	tokens->var_stop = new->var_stop;
	if ((new)->next)
	{
		tmp1 = tokens->next;
		tmp2 = new;
		tokens->next = new->next;
		tokens->next->prev = tokens;
		while (tmp2->next)
			tmp2 = tmp2->next;
		tmp1->prev = tmp2;
		tmp2->next = tmp1;
	}
	free(new);
	new = NULL;
}

static void	insert_middle(t_token *tokens, t_token *new)
{
	t_token	*tmp1;
	t_token	*tmp2;

	tmp1 = tokens;
	tmp1->prev->next = new;
	new->prev = tmp1->prev;
	tmp2 = new;
	if (new->next)
	{
		while (tmp2->next)
			tmp2 = tmp2->next;
	}
	tmp2->next = tmp1->next;
	tmp1->next->prev = tmp2;
	free(tokens->value);
	tokens->value = NULL;
	free(tokens);
	tokens = NULL;
}

static void	insert_tail(t_token *tokens, t_token *new)
{
	t_token	*tmp;

	tmp = tokens;
	tmp->prev->next = new;
	new->prev = tmp->prev;
	free(tokens->value);
	tokens->value = NULL;
	free(tokens);
	tokens = NULL;
}

void	insert_token(t_token **tokens, t_token *new)
{
	if (!(*tokens)->prev && !(*tokens)->next)
	{
		free_tokens(tokens);
		add_token(new, tokens);
		g_global.data->tokens = *tokens;
	}
	else if (!(*tokens)->prev)
		insert_head(*tokens, new);
	else if ((*tokens)->prev && (*tokens)->next)
		insert_middle(*tokens, new);
	else if (!(*tokens)->next)
		insert_tail(*tokens, new);
}
