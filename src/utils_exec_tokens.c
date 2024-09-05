/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:09:45 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/05 20:12:12 by tsantana         ###   ########.fr       */
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

static int	has_word(t_tokens_f *tkn)
{
	t_tokens_f	*tmp;

	tmp = tkn;
	while (tmp)
	{
		if (tmp->type == WORD)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

/* t_tokens_f	*token_f_order(t_tokens_f **tkn) */
/* { */
/* 	t_tokens_f	*temp; */
/* 	t_tokens_f	*temp2; */
/* 	t_tokens_f	*head; */
/* 	int			word; */
/**/
/* 	if (has_word((*tkn)) == 0) */
/* 		return ((*tkn)); */
/* 	temp = (*tkn); */
/* 	temp2 = (*tkn); */
/* 	head = (*tkn); */
/* 	word = 0; */
/* 	while (temp) */
/* 	{ */
/* 		word = 0; */
/* 		while (temp && temp->next && temp->type != PIPE) */
/* 		{ */
/* 			if (word != 1 && temp->type == WORD) */
/* 			{ */
/* 				temp->next->prev = temp->prev; */
/* 				temp->prev->next = temp->next; */
/* 				temp->prev = NULL; */
/* 				temp->next = head; */
/* 				head->prev = temp; */
/* 				word = 1; */
/* 			} */
/* 			temp = temp->next; */
/* 		} */
/* 		if (temp->next && temp->type == PIPE) */
/* 			temp = temp->next; */
/* 	} */
/* 	return (temp); */
/* } */
