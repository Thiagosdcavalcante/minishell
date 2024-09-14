/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:32:36 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/09/14 18:33:30 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numb(char a)
{
	if (a >= '0' && a <= '9')
		return (1);
	return (0);
}

int	char_comp(char *str, char *str2)
{
	int	i;

	i = 0;
	while (str[i] && str2[i])
	{
		if (str[i] > str2[i])
			return (1);
		if (str[i] < str2[i])
			return (2);
		i++;
	}
	return (0);
}

static int	size_check(char *str)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(str);
	if ((len > (ft_strlen("-9223372036854775808")))
		|| (len > (ft_strlen("+9223372036854775807")))
		|| (len > (ft_strlen("+9223372036854775807"))))
		return (1);
	if (str[0] == '-' && (len >= ft_strlen("-9223372036854775808")))
		if (ft_strncmp(str, "-9223372036854775808", 21) == 1)
			return (1);
	if (str[0] == '+' && (len >= ft_strlen("+9223372036854775807")))
		if (ft_strncmp(str, "+9223372036854775807", 21) == 1)
			return (1);
	if (is_numb(str[0]) && (len >= ft_strlen("9223372036854775807")))
		if (ft_strncmp(str, "9223372036854775807", 20) == 1)
			return (1);
	return (0);
}

static int	check_for_alphaandsignal(char *str)
{
	int	i;
	int	signal;

	i = 0;
	signal = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) > 0 || signal > 1)
			return (1);
		if (str[i] == '-' || str[i] == '+')
			signal++;
		i++;
	}
	return (0);
}

int	ft_exit(t_mini *data, char **cmd)
{
	int	i;
	int	ret;

	ret = 0;
	if (cmd == NULL)
		return (printf("exit\n"), ret % 256);
	i = 1;
	ret = 0;
	while (cmd[i])
	{
		if (i > 1)
		{
			ft_putstr_fd(" too many arguments\n", STDERR_FILENO);
			return (1);
		}
		if (check_for_alphaandsignal(cmd[i]) == 1 || size_check(cmd[i]) == 1)
			return (my_error(data, 2, "numeric argument required", "exit"), 1);
		i++;
	}
	data->exit = 1;
	i--;
	return (return_exit(cmd[i], i));
}
