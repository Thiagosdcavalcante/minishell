/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:32:36 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/09/07 11:52:41 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	define_limits(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str[i])
	{
		result += str[i] - '0';
		i++;
	}
	return (result);
}

static int	size_check(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str[i])
	{
		result += str[i] - '0';
		i++;
	}
	if (str[0] == '-')
	{
		if (result > define_limits("-9223372036854775808"))
			return (1);
	}
	else if (str[0] == '+')
	{
		if (result > define_limits("+9223372036854775807"))
			return (1);
	}
	else
	{
		if (result > define_limits("9223372036854775807"))
			return (1);
	}
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
		if (ft_isalpha(str[i]) > 0 && signal > 1)
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

	i = 1;
	ret = 0;
	data->exit = 1;
	while (cmd[i])
	{
		if (i > 1)
		{
			my_error(data, 1, "too many arguments", "exit");
			return (0);
		}
		if (check_for_alphaandsignal(cmd[i]) == 1 || (size_check(cmd[i]) == 1))
			my_error(data, 2, "numeric argument required", "exit");
		i++;
	}
	i--;
	if (cmd[1] && i == 1)
	{
		ret = ft_atoi(cmd[1]);
		if (ret < 0 && ret > -256)
			return (printf("exit\n"), (256 + ret));
	}
	return (printf("exit\n"), ret % 256);
}
