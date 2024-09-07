/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:09:45 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/07 16:21:09 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens_f	*add_special_character(t_tokens **tkn)
{
	t_tokens_f	*tkn_f;

	tkn_f = malloc(sizeof(t_tokens_f));
	tkn_f->args = NULL;
	if (!tkn_f)
		return (NULL);
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

static t_tokens_f	*tkn_f_word(t_tokens_f **tkn)
{
	t_tokens_f	*head;

	head = (*tkn);
	while (head->prev)
		head = head->prev;
	(*tkn)->next = head;
	head->prev = (*tkn);
	(*tkn)->prev = NULL;
	return ((*tkn));
}

static t_tokens_f	*tkn_f_pipe(t_tokens_f **tkn)
{
	t_tokens_f	*tmp;
	
	while ((*tkn) && (*tkn)->type != WORD)
		(*tkn) = (*tkn)->next;
	if ((*tkn) && (*tkn)->type == WORD)
	{
		if ((*tkn)->next)
		{
			tmp = (*tkn)->next;
			tmp->prev = (*tkn)->prev;
			tmp->prev->next =  tmp->next;
			tmp->next->prev = tmp->prev;
			while (tmp->prev && tmp->prev->type != PIPE)
				tmp = tmp->prev;
			tmp = tmp->prev;
			(*tkn)->prev = tmp;
			(*tkn)->next = tmp->next;
			tmp->next = (*tkn);
		}
		else
		{
			tmp = (*tkn)->prev;
			while (tmp->prev && tmp->prev->type != PIPE)
				tmp = tmp->prev;
			tmp = tmp->prev;
			(*tkn)->next = tmp->next;
			(*tkn)->prev = tmp;
			tmp->next = (*tkn);
		}
	}
	return ((*tkn));
}

t_tokens_f	*token_f_order(t_tokens_f **tkn)
{
	t_tokens_f	*head;
	t_tokens_f	*tmp;
	int			pipe;

	head = (*tkn);
	tmp = (*tkn);
	pipe = 0;
	if (tmp->type == WORD && !tmp->prev && tmp->next)
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->type == PIPE)
			pipe = 1;
		if (pipe == 0 && tmp->type == WORD)
			tmp = tkn_f_word(&tmp);
		else if (pipe == 1 && tmp->type == WORD && tmp->prev->type != PIPE)
			tmp = tkn_f_pipe(&tmp);
		tmp = tmp->next;
	}
	while (tmp)
		tmp = tmp->prev;
	head = tmp;
	return (head);
}

/* t_tokens_f	*token_f_order(t_tokens_f **tkn) */
/* { */
/* 	t_tokens_f	*tmp; */
/* 	t_tokens_f	*tmp2; */
/**/
/* 	if (!(*tkn)->prev || (*tkn)->type == WORD) */
/* 		return (*tkn); */
/* 	printf("%s\n", (*tkn)->str); */
/* 	tmp = (*tkn)->prev; */
/* 	printf("%s\n", tmp->str); */
/* 	if ((*tkn)->next && (*tkn)->prev) */
/* 	{ */
/* 		(*tkn)->next->prev = (*tkn)->prev; */
/* 		(*tkn)->prev->next = (*tkn)->next; */
/* 	} */
/* 	while (tmp && tmp->prev && tmp->prev->type != PIPE) */
/* 		tmp = tmp->prev; */
/* 	printf("%s\n", tmp->str); */
/* 	if (tmp && tmp->prev && tmp->prev->type == PIPE) */
/* 	{ */
/* 		(*tkn)->prev = tmp->prev; */
/* 		(*tkn)->prev->next = (*tkn); */
/* 		(*tkn)->next = tmp; */
/* 		tmp->prev = (*tkn); */
/* 	} */
/* 	else if (!tmp->prev) */
/* 	{ */
/* 		(*tkn)->prev = NULL; */
/* 		(*tkn)->next = tmp; */
/* 		tmp->prev = (*tkn); */
/* 	} */
/* 	printf("%s\n", tmp->str); */
/* 	while (tmp && tmp->next->type != PIPE) */
/* 		tmp = tmp->next; */
/* 	return (tmp); */
/* } */
