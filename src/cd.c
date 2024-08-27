/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:32:36 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/08/27 20:17:11 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



char	*get_env(t_mini *data, char *key)
{
	int			k;
	int			s;
	char		*result;
	t_env_list	*cur;

	cur = data->envs;
	result = NULL;
	if (key == NULL || cur == NULL)
		return (NULL);
	k = ft_strlen(key);
	while (cur)
	{
		if (ft_strncmp(cur->content, key, k) == 0)
		{
			s = k + 1;
			return (ft_substr(cur->content, s, ft_strlen(cur->content) - s));
		}
		cur = cur->next;
	}
	return (result);
}

void	update_pwd_variables(t_mini *data, char *old_pwd)
{
	char	*new_pwd;
	char	**arr_pwd;

	arr_pwd = ft_calloc(sizeof(char *), 3);
	new_pwd = getcwd(NULL, 0);
	arr_pwd[0] = ft_strjoin("OLDPWD=", old_pwd);
	arr_pwd[1] = ft_strjoin("PWD=", new_pwd);
	arr_pwd[2] = NULL;
	ft_export(data, arr_pwd);
	free(arr_pwd[0]);
	free(arr_pwd[1]);
	free(arr_pwd[2]);
	free(arr_pwd); 
	free(new_pwd); 
}

int	change_to_home_directory(t_mini *data, char *home, char *old_pwd)
{
	if (chdir(home) != 0)
	{
		free(old_pwd);
		free(home);
		perror("cd");
		return (1);
	}
	return (0);
}

int	change(t_mini *data, char *path)
{
	char	*old_pwd;
	char	*home;

	home = get_env(data, "HOME");
	old_pwd = getcwd(NULL, 0);
	if (path == NULL)
	{
		if (change_to_home_directory(data, home, old_pwd) != 0)
			return (1);
	}
	else if (chdir(path) != 0)
	{
		perror("cd");
		free(old_pwd);
		free(home);
		return (1);
	}
	update_pwd_variables(data, old_pwd);
	free(old_pwd);
	free(home);
	return (0);
}

int	ft_cd(t_mini *data, char **cmd)
{
	int	status;

	status = 0;
	if (cmd[1] == NULL)
	{
		status = change(data, NULL);
		return (0);
	}
	else if (cmd[2])
	{
		ft_putendl_fd(" too many arguments", 2);
		return (1);
	}
	status = change(data, cmd[1]);
	return (status);
}
