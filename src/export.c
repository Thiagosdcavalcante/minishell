/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:04:25 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/09/13 15:41:03 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ft_search_var(t_mini *data, char *key)
{
	t_env_list	*temp;

	temp = data->envs;
	while (temp)
	{
		if (ft_strncmp(temp->content, key, ft_strlen(key)) == 0)
			return (TRUE);
		temp = temp->next;
	}
	return (FALSE);
}

void	sorted_insert(t_env_list **head, t_env_list *node)
{
	t_env_list	*cur;
	int			size;

	size = ft_strlen(node->content);
	if (*head == NULL
		|| ft_strncmp((*head)->content, node->content, size) >= 0)
	{
		node->next = *head;
		*head = node;
	}
	else
	{
		cur = *head;
		while (cur->next != NULL
			&& ft_strncmp(cur->next->content, node->content, size) < 0)
		{
			cur = cur->next;
		}
		node->next = cur->next;
		cur->next = node;
	}
}

static int	process_env_var(t_mini *data, char *cmd)
{
	char	*key;
	char	*value;
	int		len;
	int		status;

	len = 0;
	status = 0;
	if (cmd[len] == '=')
	{
		ft_putendl_fd("export: not a valid identifier", 2);
		status = 1;
		return (status);
	}
	while (cmd[len] != '=' && cmd[len])
		len++;
	key = ft_substr(cmd, 0, len);
	value = ft_substr(cmd, ft_strlen(key) + 1, ft_strlen(cmd));
	if (ft_search_var(data, key))
		ft_update_var(data, key, value);
	else
		status = ft_create_env(data, key, value);
	free(key);
	free(value);
	return (status);
}

static int	ft_search_env(t_mini *data, char **cmd)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	if (ft_strncmp(cmd[0], "export", 7) == 0)
		i++;
	while (cmd[++i])
	{
		if (cmd[i] == NULL)
			return (status);
		status = process_env_var(data, cmd[i]);
	}
	return (status);
}

int	ft_export(t_mini *data, char **cmd)
{
	int	status;

	status = 0;
	if (cmd[1] == NULL)
		sort_export(data->envs);
	else
		status = ft_search_env(data, cmd);
	return (status);
}
