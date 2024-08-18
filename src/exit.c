/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:32:36 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/08/18 16:00:36 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	exit_aux(char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 0;
	if (!str)
		return (TRUE);
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
			sign++;
		if (ft_isalpha(str[i]) > 0 || sign > 1)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	ft_exit(t_mini *data, char **cmd)
{
	int		i;
	int		ret;

	i = 1;
	ret = 0;
	if (!cmd[i])
		exit(0);
	while (cmd[i] != NULL)
	{
		if (i > 0)
			if (exit_aux(cmd[i]) == TRUE)
				return (1);
		i++;
	}
	rl_clear_history();
	all_free(data);
	ret = ft_atoi(cmd[1]);
	ret %= 256; 
	return (ret);
}
