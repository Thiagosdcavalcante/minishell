/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:32:36 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/08/14 14:45:46 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

char	*get_env(t_mini *data, char *key)
{
	int			k;
	int			start;
	char		*result;
	t_env_list	*cur;

	cur = data->envs;
	if (key == NULL || cur == NULL)
		return (NULL);
	k = ft_strlen(key);
	while (cur)
	{
		if (ft_strncmp(cur->content, key, k) == 0)
		{
			start = k + 1;
			return (ft_substr(cur->content, start, ft_strlen(cur->content) - start));
		}
		cur = cur->next;
	}
	return (result);
}

void	change(t_data *data, char *path)
{
	char	*old_pwd;
	char	**arr_pwd;
	char	*home;

	arr_pwd = ft_calloc(sizeof(char *), 3);
	home = get_env(data, "HOME");
	old_pwd = getcwd(NULL, 0);
	if (path == NULL)
		chdir(home);
	else if (chdir(path) != 0)
	{
		perror("cd");
		free(old_pwd);
		return ;
	}
	arr_pwd[0] = ft_strjoin("OLDPWD=", old_pwd);
	arr_pwd[1] = ft_strjoin("PWD=", getcwd(NULL, 0));
	arr_pwd[2] = NULL;
	ft_export(data, arr_pwd);
	free(arr_pwd[0]);
	free(arr_pwd[1]);
	free(arr_pwd[2]);
	free(old_pwd);
	free(home);
}

void	ft_cd(t_mini *data, char **cmd)
{
	if (cmd[1] == NULL)
	{
		change(data, NULL);
		return ;
	}
	else if (cmd[2])
	{
		ft_putendl_fd("too many arguments", 2);
		return ;
	}
	change(data, cmd[1]);
	return ;
}
