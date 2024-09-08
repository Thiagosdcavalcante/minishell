/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 22:59:56 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/09/08 18:52:18 by ajuliao-         ###   ########.fr       */
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

	if (cmd[strlen(cmd) - 1] == '/')
		my_error(data, 126, "Is a directory", cmd);
	if (strncmp(cmd, "./", 2) == 0 || strncmp(cmd, "/", 1) == 0)
		path = cmd;
	else
		path = path_check(data, cmd);
	if (path == NULL)
		my_error(data, 127, "command not found", cmd);
	return (path);
}

int	ft_execute(t_mini *data, char **cmd)
{
	char	*path;
	char	**envs;
	char	**new_cmd;

	if (cmd[1] == NULL && ft_strchr(cmd[0], ' '))
		new_cmd = ft_split(cmd[0], ' ');
	else
		new_cmd = cmd;
	while (*new_cmd && strcmp(*new_cmd, "") == 0)
		new_cmd++;
	if (!new_cmd || !new_cmd[0])
		return (0);
	path = get_command_path(data, new_cmd[0]);
	if (path == NULL)
		return (127);
	if (path_exists(path) == 0)
		my_error(data, 127, "No such file or directory", new_cmd[0]);
	if (is_directory(path))
		my_error(data, 126, "Is a directory", new_cmd[0]);
	if (access(path, X_OK) != 0)
		my_error(data, 126, "Permission denied", new_cmd[0]);
	envs = env_mtx(data->envs);
	execve(path, new_cmd, envs);
	my_error(data, 126, "Execution failed", new_cmd[0]);
	return (0);
}
