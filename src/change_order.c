/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_order.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:16:40 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/10 21:11:14 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tokens_f	*order_no_pipe(t_tokens_f **tkn)
{
	t_tokens_f	*head;

	if ((*tkn)->type == WORD)
		return ((*tkn));
	head = (*tkn);
	while ((*tkn) && (*tkn)->next && (*tkn)->type != WORD && (*tkn)->type != PIPE)
		(*tkn) = (*tkn)->next;
	if ((*tkn)->type == WORD)
	{
		if ((*tkn)->next)
		{
			(*tkn)->next->prev = (*tkn)->prev;
			(*tkn)->prev->next = (*tkn)->next;
		}
		else
		(*tkn)->prev->next = NULL;
		(*tkn)->next = head;
		head->prev = (*tkn);
		(*tkn)->prev = NULL;
	}
	return ((*tkn));
}

/* static t_tokens_f	*order_with_pipe(t_tokens_f **tkn) */
/* { */
/* 	t_tokens_f	*head; */
/* 	t_tokens_f	*tmp; */
/**/
/* 	if (!(*tkn)->prev) */
/* 		(*tkn) = order_no_pipe(tkn); */
/* 	head = (*tkn); */
/* 	while ((*tkn) && (*tkn)->next && (*tkn)->type != WORD && (*tkn)->type != PIPE) */
/* 		(*tkn) = (*tkn)->next; */
/* 	if ((*tkn)->type == PIPE) */
/* 		(*tkn) = order_with_pipe(tkn); */
/* 	else if ((*tkn)->type == WORD) */
/* 	{ */
/* 		tmp = (*tkn); */
/* 		while (tmp && tmp->prev && tmp->prev->type != PIPE) */
/* 			tmp = tmp->next; */
/* 		if (tmp->prev->type == PIPE) */
/* 		{ */
/* 			tmp->prev->next = (*tkn); */
/* 			(*tkn)->prev = tmp->prev; */
/* 			(*tkn)->next = tmp; */
/* 			tmp->prev = (*tkn); */
/* 		} */
/* 	} */
/* 	return (*tkn); */
/* } */

t_tokens_f	*change_order(t_tokens_f *tkn)
{
	t_tokens_f	*head;
	t_tokens_f	*tmp;
	int			pipe;

	pipe = 0;
	head = tkn;
	tmp = tkn;
	while (tmp && tmp->next && tmp->type != WORD
		&& tmp->type != PIPE)
	{
		if (tmp->type == PIPE)
			pipe++;
		tmp = tmp->next;
	}
	/* if (pipe == 0) */
	tkn = order_no_pipe(&tkn);
	/* else */
	/* 	tkn = order_with_pipe(&tkn); */
	/* while (tkn->prev) */
	/* 	tkn = tkn->prev; */
	return (tkn);
}
