/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:29:09 by tsantana          #+#    #+#             */
/*   Updated: 2024/08/13 18:50:21 by tsantana         ###   ########.fr       */
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
	token->str = tkn->str;
	token->type = WORD;
	token->next = NULL;
	token->prev = NULL;
	token->args = make_word_exec(tkn, size);
	return (token);
}

static t_tokens_f	*make_execve_token(t_tokens_f **tkn_f, t_tokens **tkn, int word)
{
	t_tokens_f	*head;

	head = (*tkn_f);
	while ((*tkn))
	{
		if ((*tkn)->type == LESSER || (*tkn)->type == GREATER
			|| (*tkn)->type == DOUBLELESSER || (*tkn)->type == DOUBLEGREATER
			|| (*tkn)->type == MS_FILE)
			(*tkn_f)->next = add_special_character((*tkn));
		if ((*tkn)->type == PIPE)
		{
			(*tkn_f)->next = add_special_character((*tkn));
			word = 0;
		}
		if (word == 0 && (*tkn)->type == WORD)
		{
			(*tkn_f)->next = init_tokens_f((*tkn));
			word = 1;
		}
		(*tkn_f)->next->prev = (*tkn_f);
		(*tkn_f) = (*tkn_f)->next;
		(*tkn) = (*tkn)->next;
	}
	return (head);
}

t_tokens_f	*exec_tokens(t_tokens *tkn)
{
	t_tokens_f	*token_f;

	token_f = init_tokens_f(tkn);
	while (tkn && tkn->type == WORD)
		tkn = tkn->next;
	token_f = make_execve_token(&token_f, &tkn, 1);
	return (token_f);
}
