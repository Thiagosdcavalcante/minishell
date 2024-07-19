/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions_parser.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandrejuliao <alexandrejuliao@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:56:24 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/07/05 21:04:10 by alexandreju      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_lstadd_back_parser(t_parser **lst, t_parser *new)
{
	t_parser *swap;

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

t_parser *ft_lstnew_parser(int	type)
{
	t_parser *new_parser;
	
	new_parser = (t_parser *)malloc(sizeof(t_parser));
	if (new_parser == NULL)
		return NULL;
	new_parser->type = 0;
	new_parser->commands = NULL;
	new_parser->next = NULL;
	new_parser->redir = NULL;
	return new_parser;
}
