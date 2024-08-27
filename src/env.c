/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:28:08 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/08/27 20:17:30 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **environ; // revisar environ para linux

void	ft_update_var(t_mini *data, char *key, char *value)
{
	t_env_list	*data_temp;
	char		*temp;
	char		*full_temp;

	data_temp = data->envs;
	while (data_temp)
	{
		if (ft_strncmp(data_temp->content, key, ft_strlen(key)) == 0)
		{
			free(data_temp->content);
			temp = ft_strjoin(key, "=");
			full_temp = ft_strjoin(temp, value);
			free(temp);
			data_temp->content = full_temp;
		}
		data_temp = data_temp->next;
	}
}

int	ft_env(t_mini *data, char **cmd)
{
	(void)cmd;
	t_env_list	*temp;
	char		*teste;

	temp = data->envs;
	while (temp)
	{
		teste = ft_strchr(temp->content, '=');
		if(*++teste != '\0')
			ft_putendl_fd(temp->content, 1);
		temp = temp->next;
	}
	return (0);
}

void	get_envs(t_mini *data)
{
	char	*env;
    char **envp = environ;

	while(*envp)
	{
		env = ft_substr(*envp, 0, ft_strlen(*envp));
		ft_lstadd_back_env(&(data->envs), ft_lstnew_env(env));
		envp++;
	}
}

int	ft_create_env(t_mini *data, char *key, char *value)
{
	char	*content;
	char	*full_content;

	if (key[0] != '_')
	{
		if (ft_isalpha(key[0]) == 0)
		{
			ft_putendl_fd("export: not a valid identifier", 2);
			return (1);
		}
		if (ft_isalnum(key[ft_strlen(key) - 1]) == 0)
		{
			ft_putendl_fd("export: not a valid identifier", 2);
			return (1);
		}
	}
	content = ft_strjoin(key, "=");
	full_content = ft_strjoin(content, value);
	free(content);
	ft_lstadd_back_env(&(data->envs), ft_lstnew_env(full_content));
	return (0);
}
