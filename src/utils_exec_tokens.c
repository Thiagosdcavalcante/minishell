/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:09:45 by tsantana          #+#    #+#             */
/*   Updated: 2024/08/13 18:53:12 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens_f	*add_special_character(t_tokens *tkn)
{
	t_tokens_f	*tkn_f;

	tkn_f = malloc(sizeof(t_tokens_f *));
	tkn_f->next = NULL;
	tkn_f->prev = NULL;
	tkn_f->str = tkn->str;
	tkn_f->type = tkn->type;
	tkn_f->args = malloc(2 * sizeof(char **));
	tkn_f->args[0] = tkn->str;
	tkn_f->args[1] = NULL;
	return (tkn_f);
}
