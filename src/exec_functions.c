/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 22:59:56 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/08/31 15:54:12 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_paths(t_mini *data)
{
	int	i;

	i = 0;
	while (data->paths[i])
	{
		free(data->paths[i]);
		i++;
	}
	free(data->paths);
}

char	*path_check(t_mini *data, char *command)
{
	int		i;
	char	*result;
	char	*temp;

	i = 0;
	get_paths(data);
	while (data->paths[i] != NULL)
	{
		temp = ft_strjoin(data->paths[i], command); //pegar paths da env
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
	return path;
}

int	is_directory(const char *path)
{
	DIR *dir;

	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

int	path_exists(const char *path)
{
	DIR *dir;

	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return (1);
	}
	return (access(path, F_OK) == 0);
}

int	ft_execute(t_mini *data, char **cmd)
{
	char	*path;
	char	**envs;

	while (*cmd && strcmp(*cmd, "") == 0)
		cmd++;
	if (!cmd || !cmd[0])
		return (0);
	path = get_command_path(data, cmd[0]);
	if (path == NULL)
		return (127);
	if (path_exists(path) == 0)
		my_error(data, 127, "No such file or directory", cmd[0]);
	if (is_directory(path))
		my_error(data, 126, "Is a directory", cmd[0]);
	if (access(path, X_OK) != 0)
		my_error(data, 126, "Permission denied", cmd[0]);
	envs = env_mtx(data->envs);
	execve(path, cmd, envs);
	my_error(data, 126, "Execution failed", cmd[0]);
	exit(0);
}
