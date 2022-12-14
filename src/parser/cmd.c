/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 10:08:05 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/12 09:04:53 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	loop_words(char *str, int *code)
{
	int	j;
	int	k;

	j = 0;
	if (!str[j])
		return (j);
	while (str && str[j])
	{
		if (str[j] == ' ')
		{
			k = j;
			while (str && str[j] && str[j] == ' ')
				j++;
			if (!str[j])
			{
				*code = 1;
				return (k);
			}
		}
		j++;
	}
	return (j);
}

int	count_words(t_token **token, int *count)
{
	int		i;
	int		code;
	char	*str;
	t_token	*tmp;

	i = 0;
	code = 0;
	*count = 0;
	str = (*token)->value;
	if (!str[i])
		return (i);
	i = loop_words(str, &code);
	if (code)
		return (i);
	tmp = *token;
	while (tmp->next && tmp->next->type == WORD && tmp->next->value[0] != '-')
	{
		(*count)++;
		str = tmp->next->value;
		i += loop_words(str, &code);
		if (code)
			return (i);
		tmp = tmp->next;
	}
	return (i);
}

char	*join_words(t_token **token, char *str, int count, int len)
{
	char	*join;

	join = NULL;
	join = ft_strjoin(join, (*token)->value, 1);
	while ((*token)->next && (*token)->next->type == WORD && \
		(*token)->next->value[0] != '-' && count)
	{
		join = ft_strjoin(join, (*token)->next->value, 1);
		count--;
		*token = (*token)->next;
	}
	ft_strncpy(str, join, len);
	free(join);
	return (str);
}

char	*copy_cmd(t_token **token)
{
	char	*str;
	int		len;
	int		count;

	len = count_words(token, &count);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (err_msg_str(MALLOC_ERR));
	if (len == ft_strtoken((*token)->value))
		ft_strncpy(str, (*token)->value, len);
	else
		str = join_words(token, str, count, len);
	str = delete_quotes(str, str);
	return (str);
}

void	check_builtin(t_cmd *new)
{
	if (!ft_strncmp("echo", new->cmd, 5))
		new->builtin = BD_ECHO;
	else if (!ft_strncmp("cd", new->cmd, 3))
		new->builtin = BD_CD;
	else if (!ft_strncmp("pwd", new->cmd, 4))
		new->builtin = BD_PWD;
	else if (!ft_strncmp("export", new->cmd, 7))
		new->builtin = BD_EXPORT;
	else if (!ft_strncmp("unset", new->cmd, 6))
		new->builtin = BD_UNSET;
	else if (!ft_strncmp("env", new->cmd, 4))
		new->builtin = BD_ENV;
	else if (!ft_strncmp("exit", new->cmd, 5))
		new->builtin = BD_EXIT;
	else
		new->builtin = 0;
}
