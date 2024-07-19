/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandrejuliao <alexandrejuliao@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 22:59:56 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/07/08 21:47:13 by alexandreju      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*path_check(t_data *data, char *command)
{
	int		i;
	char	*result;
	char	*temp;

	i = 0;
	while (data->paths[i])
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
	// ffree(data->paths);
	if (ft_strncmp(command, "/", 1) == 0)
		if (access(command, F_OK | X_OK) == 0)
			return (command);
	my_error(data, 127, "command not found", command);
	return (0);
}

void	ft_execute(t_data *data, char *command)
{
	char	*path;
	int		len;
	char	**cmd;

	if (!command)
		return ;
	path = NULL;
	cmd = ft_split(command, ' ');
	if ((*&(cmd)) == NULL)
		my_error(data, 127, "cmd not found", " ");
	len = ft_strlen(cmd[0]);
	if (ft_strncmp(cmd[0] + len - 1, "/", 1) == 0)
		my_error(data, 126, "Is a directory", cmd[0]);
	if (ft_strncmp(cmd[0], "./", 2) != 0)
		path = path_check(data, cmd[0]);
	if (!path)
		path = cmd[0];
	if (execve(path, cmd, data->paths) < 0)
		my_error(data, errno, strerror(errno), cmd[0]);
}
