/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:19:58 by foctavia          #+#    #+#             */
/*   Updated: 2022/09/15 19:43:19 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_chars(char *str, int *i, int n)
{
	char	*value;
	int		j;

	value = malloc(sizeof(char) * (n + 1));
	if (!value)
	{
		err_msg(-2, 0);
		return (NULL);
	}
	j = 0;
	while (j < n)
	{
		value[j] = str[j];
		j++;
	}
	value[j] = '\0';
	*i += j;
	return (value);
}

char	*copy_word(char *str, int *i)
{
	int		j;
	char	*value;

	j = is_delimiter_spc(str);
	value = malloc(sizeof(char) * (j + 1));
	if (!value)
	{
		err_msg(-2, 0);
		return (NULL);
	}
	value = ft_strncpy(value, str, j);
	*i += j;
	return (value);
}

static long	countdigits(long n)
{
	int	i;

	i = 1;
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	putnbr(long n, char *str, int size)
{
	if (n > 9)
		putnbr(n / 10, str, size - 1);
	*(str + size) = n % 10 + '0';
}

char	*ft_itoa(int n)
{
	char	*str;
	long	l;
	int		size;

	size = 0;
	l = n;
	if (l < 0)
	{
		l *= -1;
		size += 1;
	}
	size += countdigits(l);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	putnbr(l, str, size - 1);
	str[size] = '\0';
	return (str);
}

char	*copy_exitstatus(int status, int *i)
{
	*i += 2;
	return (ft_itoa(status));
}

char	*copy_var(char *str, int *i)
{
	int		j;
	char	*value;

	j = is_delimiter(&str[1]) + 1;
	value = malloc(sizeof(char) * (j + 1));
	if (!value)
	{
		err_msg(-2, 0);
		return (NULL);
	}
	value = ft_strncpy(value, str, j);
	*i += j;
	return (value);
}

char	*copy_quote(char *str, int *i)
{
	char	*value;
	int		j;

	j = 1;
	value = NULL;
	while (str && str[j] && str[j] != str[0])
		j++;
	value = malloc(sizeof(char) * (j + 2));
	if (!value)
	{
		err_msg(-2, 0);
		return (NULL);
	}
	value = ft_strncpy(value, str, j + 1);
	*i += j + 1;
	return (value);
}
