/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:38:19 by foctavia          #+#    #+#             */
/*   Updated: 2022/09/09 22:34:01 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_export_error(int code, char *arg)
{
	char	*str;

	str = NULL;
	if (code == -1)
	{
		str = ft_strjoin(str, "minishell: export: ", 1);
		str = ft_strjoin(str, arg, 1);
		str = ft_strjoin(str, ": Invalid option", 1);
		printf("%s\n", str);
		free(str);
	}
	else if (code == -2)
	{
		str = ft_strjoin(str, "minishell: export: `", 1);
		str = ft_strjoin(str, arg, 1);
		str = ft_strjoin(str, "': not a valid identifier", 1);
		printf("%s\n", str);
		free(str);
	}
	return (EXIT_FAILURE);
}

int	export_env(char *str, t_env *env)
{
	int		i;
	char	*new;
	t_env	*tmp;

	i = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		return (err_msg(-2, 0));
	new = ft_strncpy(new, str, ft_strlen(str));
	while (str && str[i])
	{
		if (str[i] == '=')
			str[i + 1] = '\0';
		i++;
	}
	tmp = env;
	i = 0;
	while (tmp)
	{
		if (!ft_strncmp(tmp->val, str, ft_strlen(str)))
		{
			free(tmp->val);
			tmp->val = new;
			return (EXIT_SUCCESS);
		}
		tmp = tmp->next;
		i++;
	}
	add_env(create_env(i, new), &env);
	return (EXIT_SUCCESS);
}

int	ms_export(char *cmd, char **args, t_env *env)
{
	int		i;
	int		j;

	i = 0;
	if (!env || ft_strcmp("export", cmd))
		return (EXIT_FAILURE);
	while (args && args[i])
	{
		if (strchr(args[i], '=') && args[i][0] != '=')
			export_env(args[i], env);
		i++;
	}
	i = 0;
	while (args && args[i])
	{
		j = 0;
		if (args[i][0] == '-')
			return (ms_export_error(-1, args[i]));
		if (strchr(args[i], '=') && args[i][0] != '=')
		{
			i++;
			if (!args[i])
				break ;
		}
		else
		{
			while (args[i] && args[i][j])
			{
				if ((args[i][0] < 'A' || args[i][0] > 'Z') && \
					(args[i][0] < 'a' || args[i][0] > 'z'))
					return (ms_export_error(-2, args[i]));
				if ((args[i][j] < 'A' || args[i][j] > 'Z') && \
					(args[i][j] < 'a' || args[i][j] > 'z') && \
					(args[i][j] < '0' || args[i][j] > '9'))
					return (ms_export_error(-2, args[i]));
				j++;
			}
		}
		i++;
	}
	return(EXIT_SUCCESS);
}