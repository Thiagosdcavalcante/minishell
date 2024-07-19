/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:56:24 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/06/24 18:48:12 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_lstadd_back_env(t_env_list **lst, t_env_list *new)
{
	t_env_list	*swap;

	if (!new || !lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	swap = *lst;
	while (swap->next)
		swap = swap->next;
	swap->next = new;
}

t_env_list	*ft_lstnew_env(char *content)
{
	t_env_list	*new;

	new = (t_env_list *) malloc(sizeof(t_env_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = (NULL);
	return (new);
}
