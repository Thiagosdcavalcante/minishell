/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:09:45 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/06 16:45:00 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens_f	*add_special_character(t_tokens **tkn)
{
	t_tokens_f	*tkn_f;

	tkn_f = malloc(sizeof(t_tokens_f));
	if (!tkn_f)
		return (NULL);
	tkn_f->args = NULL;
	tkn_f->next = NULL;
	tkn_f->prev = NULL;
	tkn_f->str = (*tkn)->str;
	tkn_f->type = (*tkn)->type;
	return (tkn_f);
}

int	exec_tokens_cond(t_tokens *tkn)
{
	if (tkn->type == LESSER || tkn->type == GREATER
		|| tkn->type == DOUBLELESSER || tkn->type == DOUBLEGREATER
		|| tkn->type == MS_FILE)
		return (1);
	return (0);
}

// t_tokens_f	*token_f_order(t_tokens_f **tkn) 
// { 
// 	t_tokens_f	*tmp; 
// 	t_tokens_f	*tmp2; 

// 	if (!(*tkn)->prev || (*tkn)->type == WORD) 
// 		return (*tkn); 
// 	// printf("%s\n", (*tkn)->str); 
// 	tmp = (*tkn)->prev; 
// 	// printf("%s\n", tmp->str); 
// 	if ((*tkn)->next && (*tkn)->prev) 
// 	{ 
// 		(*tkn)->next->prev = (*tkn)->prev; 
// 		(*tkn)->prev->next = (*tkn)->next; 
// 	} 
// 	while (tmp && tmp->prev && tmp->prev->type != PIPE) 
// 		tmp = tmp->prev; 
// 	// printf("%s\n", tmp->str); 
// 	if (tmp && tmp->prev && tmp->prev->type == PIPE) 
// 	{ 
// 		(*tkn)->prev = tmp->prev; 
// 		(*tkn)->prev->next = (*tkn); 
// 		(*tkn)->next = tmp; 
// 		tmp->prev = (*tkn); 
// 	} 
// 	else if (!tmp->prev) 
// 	{ 
// 		(*tkn)->prev = NULL; 
// 		(*tkn)->next = tmp; 
// 		tmp->prev = (*tkn); 
// 	} 
// 	// printf("%s\n", tmp->str); 
// 	while (tmp && tmp->next->type != PIPE) 
// 		tmp = tmp->next; 
// 	return (tmp); 
// } 