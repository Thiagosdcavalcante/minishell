/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:04:25 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/08/17 17:40:07 by ajuliao-         ###   ########.fr       */
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

static int	ft_create_env(t_mini *data, char *key, char *value)
{
	char	*content;
	char	*full_content;

	// ft_putendl_fd(value, 2);
	if (ft_isalpha(key[0]) == 0)
	{
		ft_putendl_fd("export: not a valid identifier", 2);
		return (1);
	}
	if (ft_isalnum(key[ft_strlen(key) - 1]) == 0 )
	{
		ft_putendl_fd("export: not a valid identifier", 2);
		return (1);
	}
	content = ft_strjoin(key, "=");
	full_content = ft_strjoin(content, value);
	free(content);
	ft_lstadd_back_env(&(data->envs), ft_lstnew_env(full_content));
	return (0);
}

void	sorted_insert(t_env_list **head, t_env_list *node)
{
	t_env_list	*cur;

	if (*head == NULL
		|| ft_strncmp((*head)->content, node->content, ft_strlen(node->content)) >= 0)
	{
		node->next = *head;
		*head = node;
	}
	else
	{
		cur = *head;
		while (cur->next != NULL
			&& ft_strncmp(cur->next->content, node->content, ft_strlen(node->content)) < 0)
		{
			cur = cur->next;
		}
		node->next = cur->next;
		cur->next = node;
	}
}

static int	ft_search_env(t_mini *data, char **cmd)
{
	char	*key;
	char	*value;
	int		len;
	int		i;
	int		status;

	len = 0;
	i = -1;
	status = 0;
	if (ft_strncmp(cmd[0], "export", 7) == 0)
		i++;
	while (cmd[++i])
	{
		len = 0;
		if (cmd[i] == NULL)
			return (status) ;
		while (cmd[i][len] != '=' && cmd[i][len])
			len++;
		key = ft_substr(cmd[i], 0, len);
		value = ft_substr(cmd[i], ft_strlen(key) + 1, ft_strlen(cmd[i]));
		if (ft_search_var(data, key))
			ft_update_var(data, key, value);
		else
			status = ft_create_env(data, key, value);
		free(key);
		free(value);
	}
	return (status);
}

int	ft_export(t_mini *data, char **cmd)
{
	int status;

	status = 0;
	if (cmd[1] == NULL)
	{
		sort_export(data->envs);
	}
	else
	{
		status = ft_search_env(data, cmd);
	}
	return (status);
}
