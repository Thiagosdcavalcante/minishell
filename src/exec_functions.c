/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 22:59:56 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/08/19 23:48:01 by ajuliao-         ###   ########.fr       */
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

int	ft_execute(t_mini *data, char **cmd)
{
	char	*path;
	int		len;
	char	**envs;

	if (!cmd)
		return (1) ;
	path = NULL;
	envs = env_mtx(data->envs);
	if ((*&(cmd)) == NULL)
		my_error(data, 127, "cmd not found", " ");
	len = ft_strlen(cmd[0]);
	if (ft_strncmp(cmd[0] + len - 1, "/", 1) == 0)
		my_error(data, 126, "Is a directory", cmd[0]);
	if (ft_strncmp(cmd[0], "./", 2) != 0)
		path = path_check(data, cmd[0]);
	if (!path)
		path = cmd[0];
	if (execve(path, cmd, envs) < 0)
		my_error(data, errno, strerror(errno), cmd[0]);
	return (1);
}
