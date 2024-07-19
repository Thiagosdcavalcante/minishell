/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions_commands.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandrejuliao <alexandrejuliao@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:56:24 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/07/05 21:04:05 by alexandreju      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_lstadd_back_commands(t_commands **lst, t_commands *new)
{
	t_commands *swap;

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

t_commands *ft_lstnew_commands(char *word)
{
	t_commands *new_command;
	
	new_command = (t_commands *)malloc(sizeof(t_commands));
	if (new_command == NULL)
		return NULL;
	new_command->word = ft_strdup(word);
	new_command->next = NULL;
	return new_command;
}
