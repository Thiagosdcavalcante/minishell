/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:26:23 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/09/13 15:36:03 by ajuliao-         ###   ########.fr       */
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
	if (cmd[i][0] != '_')
		{
			if (ft_isalpha(cmd[i][0]) == 0)
				printf("unset: \"%s\": not a valid identifier\n", cmd[i]);
			else if (ft_isalnum(cmd[i][ft_strlen(cmd[i]) - 1]) == 0)
				return(printf("unset: \"%s\": not a valid identifier\n", cmd[i]), 1);
		}
		ft_remove_env(data, cmd[i]);
	}
	return (0);
}
