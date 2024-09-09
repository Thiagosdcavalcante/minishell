/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_order.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:16:40 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/09 20:01:56 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens_f	*change_order(t_tokens_f *tkn)
{
	t_tokens_f	*head;

	if (tkn->type == WORD)
		return (tkn);
	head = tkn;
	while (tkn && tkn->next && tkn->type != WORD && tkn->type != PIPE)
		tkn = tkn->next;
	if (tkn->type == WORD)
	{
		if (tkn->next)
		{
			tkn->next->prev = tkn->prev;
			tkn->prev->next = tkn->next;
		}
		else
			tkn->prev->next = NULL;
		tkn->next = head;
		head->prev = tkn;
		tkn->prev = NULL;
	}
	return (tkn);
}
