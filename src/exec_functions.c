/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 22:59:56 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/09/14 18:59:06 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	support_for_ft_execute(char *path, char **new_cmd, t_mini *data)
{
	if (path_exists(path) == 0)
		my_error(data, 127, "No such file or directory", new_cmd[0]);
	if (is_directory(path))
		my_error(data, 126, "Is a directory", new_cmd[0]);
	if (access(path, X_OK) != 0)
		my_error(data, 126, "Permission denied", new_cmd[0]);
}

int	ft_execute(t_mini *data, char **cmd)
{
	char	*path;
	char	**envs;
	char	**new_cmd;

	if (cmd[1] == NULL && ft_strchr(cmd[0], ' ')
		&& check_if_only_spaces(cmd[0]) == FALSE)
		new_cmd = ft_split(cmd[0], ' ');
	else
		new_cmd = cmd;
	while (*new_cmd && ft_strcmp(*new_cmd, "") == 0)
		new_cmd++;
	if (!new_cmd || !new_cmd[0])
		return (0);
	path = get_command_path(data, new_cmd[0]);
	if (path == NULL)
		return (127);
	support_for_ft_execute(path, new_cmd, data);
	envs = env_mtx(data->envs);
	execve(path, new_cmd, envs);
	my_error(data, 126, "Execution failed", new_cmd[0]);
	return (0);
}
