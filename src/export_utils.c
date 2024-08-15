/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:04:25 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/08/14 20:02:58 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insertion_sort(t_env_list **head)
{
	t_env_list	*sorted;
	t_env_list	*current;
	t_env_list	*next;

	current = *head;
	sorted = NULL;
	while (current != NULL)
	{
		next = current->next;
		sorted_insert(&sorted, current);
		current = next;
	}
	*head = sorted;
}

t_env_list	*create_node(char *content)
{
	t_env_list	*new_node;

	new_node = (t_env_list *)malloc(sizeof(t_env_list));
	if (!new_node)
		return (NULL);
	new_node->content = strdup(content);
	new_node->next = NULL;
	return (new_node);
}

void	free_list(t_env_list *head)
{
	t_env_list	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->content);
		free(tmp);
	}
}

void	print_list(t_env_list *node)
{
	while (node != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(node->content, 1);
		node = node->next;
	}
}

void	sort_export(t_env_list *envs)
{
	t_env_list	*temp;
	t_env_list	*head;
	t_env_list	*new_node;

	temp = envs;
	head = NULL;
	while (temp)
	{
		new_node = create_node(temp->content);
		if (!new_node)
		{
			free_list(head);
			return ;
		}
		new_node->next = head;
		head = new_node;
		temp = temp->next;
	}
	insertion_sort(&head);
	print_list(head);
	free_list(head);
}
