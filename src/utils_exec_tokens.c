/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:09:45 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/12 21:52:17 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens_f	*add_special_character(t_tokens **tkn)
{
	t_tokens_f	*tkn_f;

	tkn_f = malloc(sizeof(t_tokens_f));
	if (!tkn_f)
		return (NULL);
	tkn_f->args = NULL;
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

int	n_args(char **args)
{
	int	i;

	if (!args)
		return (0);
	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	is_file(int type)
{
	if (type == DOUBLELESSER || type == DOUBLEGREATER
		|| type == LESSER || type == GREATER)
		return (TRUE);
	return (FALSE);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
