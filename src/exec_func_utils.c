/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_func_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:10:10 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/14 18:59:02 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*path_check(t_mini *data, char *command)
{
	int		i;
	char	*result;
	char	*temp;

	i = 0;
	get_paths(data, command);
	while (data->paths[i] != NULL)
	{
		temp = ft_strjoin(data->paths[i], command);
		if (access(temp, F_OK | X_OK) == 0)
		{
			result = ft_strjoin(data->paths[i], command);
			free(temp);
			return (result);
		}
		free(temp);
		i++;
	}
	if (ft_strncmp(command, "/", 1) == 0)
		if (access(command, F_OK | X_OK) == 0)
			return (command);
	my_error(data, 127, "command not found", command);
	return (0);
}

int	ft_lstsize_env(t_env_list *lst)
{
	int	count;

	count = 1;
	if (!lst)
		return (0);
	while (lst->next != NULL)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

char	**env_mtx(t_env_list *envs)
{
	char		**new_envs;
	int			len;
	t_env_list	*temp;

	len = ft_lstsize_env(envs);
	new_envs = ft_calloc(sizeof (char *), len + 1);
	temp = envs;
	len = 0;
	while (temp)
	{
		new_envs[len++] = temp->content;
		temp = temp->next;
	}
	return (new_envs);
}

char	*get_command_path(t_mini *data, char *cmd)
{
	char	*path;

	if (cmd[ft_strlen(cmd) - 1] == '/')
		my_error(data, 126, "Is a directory", cmd);
	if (ft_strncmp(cmd, "./", 2) == 0 || ft_strncmp(cmd, "/", 1) == 0)
		path = cmd;
	else
		path = path_check(data, cmd);
	if (path == NULL)
		my_error(data, 127, "command not found", cmd);
	return (path);
}

int	has_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_isspace(str[i]);
		i++;
	}
	return (1);
}
