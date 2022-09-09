/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:56:15 by foctavia          #+#    #+#             */
/*   Updated: 2022/09/09 22:16:47 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_env(t_env *new, t_env **env)
{
	t_env	*tmp;

	if (!env)
		return (EXIT_FAILURE);
	if (*env)
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
	else
		*env = new;
	return (EXIT_SUCCESS);
}

t_env	*create_env(int	i, char *val)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		err_msg(-2, 0);
		return (NULL);
	}
	new->i = i;
	new->val = val;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

int	copy_env(t_data *data, char **env)
{
	int		i;
	char	*val;

	i = 0;
	val = NULL;
	if (!env || !env[i] || !data)
		return (EXIT_FAILURE);
	while (env && env[i] && !g_global.data->err)
	{
		val = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		if (!val)
			return (err_msg(-2, 0));
		val = ft_strncpy(val, env[i], ft_strlen(env[i]));
		if (add_env(create_env(i, val), &data->shell.env))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}