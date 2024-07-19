/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:56:23 by tsantana          #+#    #+#             */
/*   Updated: 2024/07/09 15:56:31 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

t_envs	*make_env_nodes(char *str)
{
	t_envs	*env;
	int		equal;
	char	*str1;

	str1 = ft_strchr(str, '=');
	equal = str1 - str;
	env = malloc(sizeof(t_envs));
	env->envcontent = ft_strdup(++str1);
	env->envkey = ft_substr(str, 0, equal);
	env->next = NULL;
	return (env);
}

void	get_paths(t_mini *data, t_envs *envs)
{
	int		i;
	char	*temp;
	t_envs	*envp;

	i = 0;
	envp = envs;
	while (ft_strncmp(envp->envkey, "PATH", 5))
		envp = envp->next;
	data->paths = ft_split(envp->envcontent, ':');
	temp = data->paths[0];
	data->paths[0] = ft_substr(temp, 5, ft_strlen(temp));
	free(temp);
	while (data->paths[i] != NULL)
	{
		temp = data->paths[i];
		data->paths[i] = ft_strjoin(temp, "/");
		free(temp);
		i++;
	}
}
// void	add_env_var()
// {
//
// }

t_envs	*get_envs(char **original)
{
	int		i;
	t_envs	*envs;
	t_envs	*head;

	i = 1;
	envs = make_env_nodes(original[0]);
	head = envs;
	while (original[i])
	{
		envs->next = make_env_nodes(original[i]);
		envs = envs->next;
		i++;
	}
	return (head);
}
