/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:26:23 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/08/14 15:44:03 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_mini *data, char **cmd)
{
	t_env_list	*data_temp;
	t_env_list	*temp;
	int			i;

	i = 0;
	while (cmd[++i] != NULL)
	{
		temp = NULL;
		data_temp = data->envs;
		while (data_temp != NULL)
		{
			if (ft_strncmp(data_temp->content, cmd[i], ft_strlen(cmd[i])) == 0)
			{
				if (temp == NULL)
					data->envs = data_temp->next;
				else
					temp->next = data_temp->next;
				free(data_temp->content);
				free(data_temp);
				if (temp == NULL && data_temp->next == NULL)
					data->envs = NULL;
				data_temp = data->envs ;
			}
			temp = data_temp;
			data_temp = data_temp->next;
		}
	}
}
