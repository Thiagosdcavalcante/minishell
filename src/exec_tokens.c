/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 19:29:09 by tsantana          #+#    #+#             */
/*   Updated: 2024/08/07 16:32:04 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_size_mtx(t_tokens *tkn)
{
	t_tokens	*temp;
	int			size;
	int			total;

	temp = tkn;
	size = 1;
	total = 0;
	while (temp)
	{
		if (temp->type == LESSER)
			size++;
		else if (temp->type == GREATER)
			size++;
		else if (temp->type == DOUBLEGREATER)
			size++;
		else if (temp->type == DOUBLELESSER)
			size++;
		else if (temp->type == MS_FILE)
			size++;
		else if (temp->type == WORD && total != 0)
			size++;
		else if (temp->type == PIPE)
		{
			size++;
			total += size;
			size = 0;
		}
		temp = temp->next;
	}
	return (total);
}

t_tokens_f	*exec_tokens(t_tokens *tkn)
{
	int	size;
	int	pipe;
	int	pointers;

	size = check_size_mtx(tkn);
}
