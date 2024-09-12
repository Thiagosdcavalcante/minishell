/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:26:23 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/09/12 18:17:57 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_remove_env(t_mini *data, char *cmd)
{
	t_env_list	*data_temp;
	t_env_list	*temp;

	temp = NULL;
	data_temp = data->envs;
	while (data_temp != NULL)
	{
		if (ft_strncmp(data_temp->content, cmd, ft_strlen(cmd)) == 0)
		{
			if (temp == NULL)
				data->envs = data_temp->next;
			else
				temp->next = data_temp->next;
			free(data_temp->content);
			free(data_temp);
			if (temp == NULL && data_temp->next == NULL)
				data->envs = NULL;
			data_temp = data->envs;
		}
		else
		{
			temp = data_temp;
			data_temp = data_temp->next;
		}
	}
}

int	ft_unset(t_mini *data, char **cmd)
{
	int	i;

	i = 0;
	while (cmd[++i] != NULL)
	{
		ft_remove_env(data, cmd[i]);
		return (0);
	}
	return (0);
}
