/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 21:36:17 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/07/06 11:25:37 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_lstadd_back_tokens(t_tokens **lst, t_tokens *new)
{
	t_tokens *swap;

	if (!new || !lst)
		return;
	if (*lst == NULL)
	{
		*lst = new;
		return;
	}
	swap = *lst;
	while (swap->next)
		swap = swap->next;
	swap->next = new;
}

t_tokens	*ft_lstlast_token(t_tokens *lst)
{
	t_tokens	*current;

	if (!lst)
		return (NULL);
	current = lst;
	while (current->next != NULL)
		current = current->next;
	return (current);
}

t_tokens *ft_lstnew_tokens(t_tokens *list, char *content, int type)
{
	t_tokens *new_tokens;
	
	new_tokens = (t_tokens *)malloc(sizeof(t_tokens));
	if (new_tokens == NULL)
		return NULL;
	new_tokens->type = type;
	new_tokens->word = ft_strdup(content);
	new_tokens->next = NULL;
	new_tokens->prev = ft_lstlast_token(list);
	return new_tokens;
}
