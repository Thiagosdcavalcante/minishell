/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:29:09 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/12 22:17:13 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**make_word_exec(t_tokens *tkn, int size)
{
	char	**args;
	int		i;

	i = 0;
	args = malloc((size + 1) * sizeof(char *));
	while (tkn && i < size)
	{
		if (tkn->type == WORD)
		{
			args[i] = tkn->str;
			i++;
		}
		tkn = tkn->next;
	}
	args[i] = NULL;
	return (args);
}

static int	check_array_size(t_tokens *tkn)
{
	t_tokens	*temp;
	int			i;

	temp = tkn;
	i = 0;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == WORD)
			i++;
		temp = temp->next;
	}
	return (i);
}

static t_tokens_f	*init_tokens_f(t_tokens *tkn)
{
	int			size;
	t_tokens_f	*token;

	size = check_array_size(tkn);
	token = malloc(sizeof(t_tokens_f));
	if (!token)
		return (NULL);
	token->str = tkn->str;
	token->type = tkn->type;
	token->next = NULL;
	token->prev = NULL;
	if (exec_tokens_cond(tkn))
		token->args = NULL;
	else
		token->args = make_word_exec(tkn, size);
	return (token);
}

t_tokens_f	*make_exec_token(t_tokens_f **tkn_f, t_tokens **tkn, int word)
{
	t_tokens_f	*head;

	head = (*tkn_f);
	while ((*tkn))
	{
		if (exec_tokens_cond((*tkn)))
			(*tkn_f)->next = add_special_character(tkn);
		else if ((*tkn)->type == PIPE)
		{
			(*tkn_f)->next = add_special_character(tkn);
			word = 0;
		}
		else if (word == 0 && (*tkn)->type == WORD)
		{
			(*tkn_f)->next = init_tokens_f((*tkn));
			word = 1;
		}
		if ((*tkn_f)->next)
		{
			(*tkn_f)->next->prev = (*tkn_f);
			(*tkn_f) = (*tkn_f)->next;
		}
		(*tkn) = (*tkn)->next;
	}
	return (head);
}

t_tokens_f	*exec_tokens(t_tokens *tkn)
{
	t_tokens_f	*token_f;
	int			cond;

	token_f = init_tokens_f(tkn);
	if (tkn->type == WORD)
		cond = 1;
	else
		cond = 0;
	if (exec_tokens_cond(tkn))
		tkn = tkn->next;
	token_f = make_exec_token(&token_f, &tkn, cond);
	return (token_f);
}
