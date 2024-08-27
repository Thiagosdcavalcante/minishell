/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:10:50 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/08/27 19:46:24 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_paths(t_mini *data)
{
	int		i;
	char	*temp;
	char	*env;

	// i = 0;
	// if (data->paths)
	// {
	// 	while (data->paths[i] != NULL)
	// 	{
	// 		free(data->paths[i++]);
	// 	}
	// 	data->paths[i] = NULL;
	// }
	i = 0;
	env = get_env(data, "PATH");
	data->paths = ft_split(env, ':');
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
	free(env);
}

void	ffree(t_mini *data)
{
	int			i;
	t_env_list	*temp;

	if (data->paths)
	{
		i = 0;
		while (data->paths[i] != NULL)
		{
			free(data->paths[i]);
			i++;
		}
		free(data->paths);
	}
	if (data->envs)
	{
		while (data->envs)
		{
			temp = data->envs->next;
			free(data->envs->content);
			free(data->envs);
			data->envs = temp;
		}
	}
}
void	all_free(t_mini *data)
{
	if (data->in_ms)
		free(data->in_ms);
	if (data->cmmds)
		free_tokens(data->cmmds);
	if (data->tokens)
		free_tokens_f(data->tokens);
	if (data->tree)
		free_tree(data->tree);
	data->in_ms = NULL;
}

char	*ft_put_zero(void)
{
	static int	nbr;

	nbr++;
	return (ft_itoa(nbr));
}

void	print_list_export(t_env_list *node)
{
	while (node != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(node->content, 1);
		node = node->next;
	}
}
