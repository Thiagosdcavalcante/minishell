/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:56:02 by tsantana          #+#    #+#             */
/*   Updated: 2024/08/07 13:37:18 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	search_type(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '|' && !str[i + 1])
		return (PIPE);
	else if (str[i] == '>' && !str[i + 1])
		return (GREATER);
	else if (str[i] == '<' && !str[i + 1])
		return (LESSER);
	else if (str[i] == '<' && str[i + 1] == '<')
		return (DOUBLELESSER);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (DOUBLEGREATER);
	else
		return (WORD);
}

static int	is_file(int type)
{
	if (type == DOUBLELESSER || type == DOUBLEGREATER
		|| type == LESSER || type == GREATER)
		return (TRUE);
	return (FALSE);
}


static t_tokens	*define_word(t_tokens *lst)
{
	t_tokens	*temp;
	t_tokens	*head;

	head = lst;
	temp = lst;
	while (temp)
	{
		if (temp->prev && temp->type == WORD && is_file(temp->prev->type))
			temp->type = MS_FILE;
		temp = temp->next;
	}
	return (head);
}

static t_tokens	*create_mtx(char *str)
{
	t_tokens	*ms;

	ms = malloc(sizeof(t_tokens));
	if (!ms)
		return (NULL);
	ms->str = ft_strdup(str);
	ms->type = search_type(str);
	ms->next = NULL;
	ms->prev = NULL;
	return (ms);
}

t_tokens	*parse_str(char *str)
{
	char		**parse_str;
	t_tokens	*mtx;
	t_tokens	*head;
	int			i;

	if (!str)
		return (NULL);
	i = 0;
	mtx = NULL;
	parse_str = custom_split(str, ' ');
	mtx = create_mtx(parse_str[i]);
	if (!mtx)
		return (NULL);
	head = mtx;
	i++;
	while (parse_str[i])
	{
		mtx->next = create_mtx(parse_str[i]);
		mtx->next->prev = mtx;
		mtx = mtx->next;
		i++;
	}
	free_split(parse_str);
	return (define_word(head));
}
