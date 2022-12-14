/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:56:15 by foctavia          #+#    #+#             */
/*   Updated: 2022/10/11 15:26:38 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_substr(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

static void	free_str(char **str, int i)
{
	while (i >= 0)
		free(str[i--]);
	free(str);
}

int	copy_substr(char **new_env, char **env, int substr)
{
	int	i;

	i = 0;
	while (env[i] && i < substr)
	{
		new_env[i] = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		if (!new_env[i])
		{
			free_str(new_env, i);
			return (err_msg(MALLOC_ERR, 0, 1));
		}
		ft_strncpy(new_env[i], env[i], ft_strlen(env[i]));
		i++;
	}
	new_env[substr] = NULL;
	return (EXIT_SUCCESS);
}

int	create_env(t_data *data)
{
	char	**env;

	env = (char **)malloc(sizeof(char *) * 2);
	if (!env)
		return (EXIT_FAILURE);
	env[0] = ft_strndup("PATH=/bin", 10);
	env[1] = NULL;
	data->shell.env = env;
	return (EXIT_SUCCESS);
}

int	copy_env(t_data *data, char **env)
{
	char	**new_env;
	char	*shlvl;
	int		substr;
	int		i;

	i = 0;
	substr = 0;
	if (!env || !env[i] || !data)
		return (create_env(data));
	substr = count_substr(env);
	if (!substr)
		return (EXIT_FAILURE);
	new_env = malloc(sizeof(char *) * (substr + 1));
	if (!new_env)
		return (err_msg(MALLOC_ERR, 0, 1));
	if (copy_substr(new_env, env, substr))
		return (EXIT_FAILURE);
	data->shell.env = new_env;
	shlvl = ft_getenv("SHLVL");
	if (shlvl)
	{
		data->shell.shlvl = ft_atoi(shlvl) + 1;
		free(shlvl);
	}
	return (EXIT_SUCCESS);
}
