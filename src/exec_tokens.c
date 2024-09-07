/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:29:09 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/06 16:45:15 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// char	**make_word_exec(t_tokens *tkn, int size)
// {
// 	char	**args;
// 	int		i;

// 	i = 0;
// 	args = malloc((size + 1) * sizeof(char *));
// 	while (tkn && i < size)
// 	{
// 		if (tkn->type == WORD)
// 		{
// 			args[i] = tkn->str;
// 			i++;
// 		}
// 		tkn = tkn->next;
// 	}
// 	args[i] = NULL;
// 	return (args);
// }

// static int	check_array_size(t_tokens *tkn)
// {
// 	t_tokens	*temp;
// 	int			i;

// 	temp = tkn;
// 	i = 0;
// 	while (temp && temp->type != PIPE)
// 	{
// 		if (temp->type == WORD)
// 			i++;
// 		temp = temp->next;
// 	}
// 	return (i);
// }

// static t_tokens_f	*init_tokens_f(t_tokens *tkn)
// {
// 	int			size;
// 	t_tokens_f	*token;

// 	size = check_array_size(tkn);
// 	token = malloc(sizeof(t_tokens_f));
// 	if (!token)
// 		return (NULL);
// 	token->str = tkn->str;
// 	token->type = tkn->type;
// 	token->next = NULL;
// 	token->prev = NULL;
// 	if (exec_tokens_cond(tkn) == 1)
// 		token->args = NULL;
// 	else
// 		token->args = make_word_exec(tkn, size);
// 	return (token);
// }

// static t_tokens_f	*make_execve_token(t_tokens_f **tkn_f, t_tokens **tkn, int word)
// {
// 	t_tokens_f	*head;

// 	head = (*tkn_f);
// 	while ((*tkn))
// 	{
// 		if (exec_tokens_cond(*tkn) == 1)
// 			(*tkn_f)->next = add_special_character(tkn);
// 		else if ((*tkn)->type == PIPE)
// 		{
// 			(*tkn_f)->next = add_special_character(tkn);
// 			word = 0;
// 		}
// 		else if (word == 0 && (*tkn)->type == WORD)
// 		{
// 			(*tkn_f)->next = init_tokens_f((*tkn));
// 			word = 1;
// 		}
// 		if ((*tkn_f)->next)
// 		{
// 			(*tkn_f)->next->prev = (*tkn_f);
// 			(*tkn_f) = (*tkn_f)->next;
// 		}
// 		(*tkn) = (*tkn)->next;
// 	}
// 	return (head);
// }

// static void	print_tknf(t_tokens_f *tkn)
// {
// 	while (tkn)
// 	{
// 		printf("STR: %s | TYPE: %d\n", tkn->str, tkn->type);
// 		tkn = tkn->next;
// 	}
// }

// t_tokens_f	*exec_tokens(t_tokens *tkn)
// {
// 	t_tokens_f	*token_f;
// 	t_tokens_f	*temp;

// 	token_f = init_tokens_f(tkn);
// 	if (exec_tokens_cond(tkn) == 1)
// 		tkn = tkn->next;
// 	token_f = make_execve_token(&token_f, &tkn, 1);
// 	print_tknf(token_f);
// 	temp = token_f;
// 	while (temp->next)
// 	{
// 		if (temp->next->type == WORD)
// 			temp = token_f_order(&temp->next);
// 		temp = temp->next;
// 	}
// 	while (temp->prev)
// 		temp = temp->prev;
// 	// print_tknf(temp);
// 	token_f = temp;
// 	print_tknf(token_f);
// 	return (token_f);
// }

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
	if (tkn->type == LESSER || tkn->type == GREATER
			|| tkn->type == DOUBLELESSER || tkn->type == DOUBLEGREATER
			|| tkn->type == MS_FILE)
	{
		token->args = NULL;
	}
	else
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
	// t_tokens_f	*head;

	token_f = init_tokens_f(tkn);
	if (tkn->next && (tkn->type == LESSER || tkn->type == GREATER
			|| tkn->type == DOUBLELESSER || tkn->type == DOUBLEGREATER
			|| tkn->type == MS_FILE))
	{
		tkn = tkn->next;
	}
	token_f = make_execve_token(&token_f, &tkn, 1);
	// head = token_f;
	// while (token_f)
	// {
	// 	if (token_f->next)
	// 		token_f = token_f->next;
	// 	else
	// 		break ;
	// }
	return (token_f);
}
