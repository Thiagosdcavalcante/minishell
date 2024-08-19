/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:32:36 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/08/16 18:34:21 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_mini *data, char **cmd)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	j = 0;
	ret = 0;
	while (*cmd[i++])
	{
		if (i > 0)
		{
			while (cmd[i][j++])
			{
				if (ft_isalpha(cmd[i][j]) > 0)
					return (2);
				j++;
			}
		}
	}
	// rl_clear_history();
	all_free(data);
	data->exit = 0;
	ret = ft_atoi(cmd[1]);
	exit(ret);
}
