/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:28:02 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/09 22:14:28 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exit_error(int code)
{
	if (code == -1)
		printf("Too many args in function call\n");
	else if (code == -2)
		printf("Argument is not numeric\n");
}

int	check_flag(char *arg)
{
	int	i;

	i = 0;
	while (arg && arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			ms_exit_error(-2);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	clean_exit(t_env **env)
{
	t_env	*tmp;
	t_env	*next;
	
	if (*env)
	{
		tmp = *env;
		while (tmp)
		{
			next = tmp->next;
			if (tmp->val)
				free(tmp->val);
			free(tmp);
			tmp = next;
		}
	}
	return (EXIT_SUCCESS);
}

int	ms_exit(char *cmd, char **args, t_env *env)
{
	if (ft_strcmp("exit", cmd))
		return (EXIT_FAILURE);
	if (args && args[0])
	{
		ms_exit_error(-1);
		return (EXIT_FAILURE);
	}
	else if (args && args[0] && !check_flag(args[0]))
		exit(atoi(args[0]));
	else
		exit(clean_exit(&env));
}
