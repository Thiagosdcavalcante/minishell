/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:02:22 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/08/14 14:45:16 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_has_n(char **cmd)
{
	int	i;
	int	j;

	i = 1;
	if (cmd[i] == NULL)
		return (i);
	while (cmd[i] != NULL)
	{
		if (ft_strncmp(cmd[i], "-n", 2) == 0)
		{
			j = 2;
			while (cmd[i][j] != '\0' && cmd[i][j] == 'n')
				j++;
			if (cmd[i][j] != '\0')
				break ;
		}
		else
			break ;
		i++;
	}
	return (i);
}

void	ft_echo(t_mini *data, char **cmd)
{
	int	i;

	init_expansion(data, cmd);
	if (cmd[1] == NULL)
	{
		ft_putchar_fd('\n', 1);
		return ;
	}
	i = ft_has_n(cmd);
	while (cmd[i])
	{
		if (i > 1)
		{
			ft_putstr_fd(cmd[i], 1);
			if (cmd[i + 1] != NULL)
				ft_putchar_fd(' ', 1);
		}
		else
		{
			ft_putstr_fd(cmd[i], 1);
			ft_putchar_fd(' ', 1);
		}
		i++;
	}
	if (ft_has_n(cmd) == 1)
		ft_putchar_fd('\n', 1);
	return ;
}
