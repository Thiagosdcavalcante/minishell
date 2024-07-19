/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcarrara <vcarrara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:28:08 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/06/30 13:08:59 by vcarrara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_unset(t_data *data, char *key)
{
	t_env_list	*data_temp;
	t_env_list	*temp;

	temp = NULL;
	data_temp = data->envs;
	while (data_temp != NULL)
	{
		if (ft_strncmp(data_temp->content, key, ft_strlen(key)) == 0)
		{
			if (temp == NULL)
				data->envs = data_temp->next;
			else
				temp->next = data_temp->next;
			free(data_temp->content);
			free(data_temp);
			if (temp == NULL && data_temp->next == NULL)
				data->envs = NULL;
			return ;
		}
		temp = data_temp;
		data_temp = data_temp->next;
	}
}

void	ft_export(t_data *data, char *content)
{
	char	*key;
	char	*value;
	int		len;

	len = 0;
	while (content[len] != '=')
		len++;
	key = ft_substr(content, 0, len);
	value = ft_substr(content, ft_strlen(key) + 1, ft_strlen(content));
	if (ft_search_var(data, key))
		ft_update_var(data, key, value);
	else
		ft_create_env(data, key, value);
	free(key);
	free(value);
}

void	ft_create_env(t_data *data, char *key, char *value)
{
	char	*content;
	char	*full_content;
	char	*final;

	content = ft_strjoin(key, "=");
	full_content = ft_strjoin(content, value);
	free(content);
	ft_lstadd_back_env(&(data->envs), ft_lstnew_env(full_content));
}

void	ft_env(t_data *data)
{
	t_env_list	*temp;

	temp = data->envs;
	while (temp)
	{
		// if(ft_strchr(temp->content, '='))
		ft_putendl_fd(temp->content, 2);
		temp = temp->next;
	}
}
