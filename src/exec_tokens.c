/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:29:09 by tsantana          #+#    #+#             */
/*   Updated: 2024/08/05 20:28:35 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_tokens_f	*init_token_f(t_tokens *head, t_tokens_f *new_tkn)
{

}

static t_tokens_f	*double_tokens(t_tokens **head, t_tokens_f **new_tkn)
{
	if ((*head)->type == DOUBLELESSER)
	{
		(*new_tkn)->str = &(*head)->str;
		(*new_tkn)->type = DOUBLELESSER;
		(*new_tkn)->token[0] = &(*head)->str;
		return ((*new_tkn));
	}
	else if ((*head)->type == DOUBLEGREATER)
	{
		(*new_tkn)->str = &(*head)->str;
		(*new_tkn)->type = DOUBLEGREATER;
		(*new_tkn)->token[0] = &(*head)->str;
		return ((*new_tkn));
	}

}

static t_tokens	*token_special_char(t_token **head, t_token_f **new_tkn)
{
	if ((*head)->type == PIPE)
	{
		(*new_tkn)->str = &(*head)->str;
		(*new_tkn)->type = PIPE;
		(*new_tkn)->token[0] = &(*head)->str;
		return ((*new_tkn));
	}
	else if ((*head)->type == GREATER)
	{
		(*new_tkn)->str = &(*head)->str;
		(*new_tkn)->type = GREATER;
		(*new_tkn)->token[0] = &(*head)->str;
		return ((*new_tkn));
	}
	else if ((*head)->type == LESSER)
	{
		(*new_tkn)->str = &(*head)->str;
		(*new_tkn)->type = LESSER;
		(*new_tkn)->token[0] = &(*head)->str;
		return ((*new_tkn));
	}
	else if ((*head)->type == DOUBLEGREATER || (*head)->type == DOUBLELESSER)
		return (double_tokens(head, new_tkn));
}

t_tokens_f	*new_exec_token(t_tokens *head)
{
	t_tokens_f	*token;
	int			i;

	i = 0;
	token = malloc(sizeof(t_tokens_f *));
	token->args = 
	token = init_token_f(head, token);
	while (head
		&& !(head->type == WORD || head->type == CMMND || head->type == PARAM))
	{
		head = head->next;
	}
}

t_tokens_f	*create_exec_tokens(t_tokens *head)
{
	t_tokens	*tkns;
	t_tokens_f	*exec_t;

	tkns = head;
	while (tkns)
	{
		while (tkns->type != PIPE)
		{
			if (tkns->type == WORD || tkns->type == CMMND || tkns->type == PARAM)
			{
				exec_t->next = new_exec_token(tkns);
				exec_t = exec_t->next;
			}
			if (head->type != CMMND || head->type != WORD || head->type != PARAM)
				return (add_special_char(head, token));
			tkns = tkns->next;
		}
	}

}
