/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:29:09 by tsantana          #+#    #+#             */
/*   Updated: 2024/08/10 23:12:27 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static void	make_args(t_tokens *tkn, t_tokens_f **tokens) */
/* { */
/* 	t_tokens	*temp; */
/* 	int			i; */
/* 	int			j; */
/**/
/* 	temp = tkn; */
/* 	i = 0; */
/* 	j = 0; */
/* 	while (temp && temp->type != PIPE) */
/* 	{ */
/* 		if (temp->type == WORD) */
/* 		{ */
/* 			(*token)->args[i][j] = &temp->str; */
/* 			j++; */
/* 		} */
/* 		i++; */
/* 		temp = temp->next; */
/* 	} */
/* } */

static t_tokens_f	*init_tokens_f(t_tokens *tkn)
{
	int			size;
	int			i;
	t_tokens	*tmp;
	t_tokens_f	*token;

	tmp = tkn;
	size = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
			size++;
		tmp = tmp->next;
	}
	tmp = tkn;
	token = malloc(sizeof(t_tokens_f));
	token->str = &tmp->str;
	token->type = WORD;
	token->next = NULL;
	token->prev = NULL;
	token->args = ft_calloc(size * sizeof(char *));
	return (token);
}

t_tokens_f	*exec_tokens(t_tokens *tkn)
{
	t_tokens_f	*token_f;

	token_f = init_tokens(tkn);
	return (token_f);
}
