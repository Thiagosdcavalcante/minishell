/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:56:02 by tsantana          #+#    #+#             */
/*   Updated: 2024/07/03 19:55:53 by tsantana         ###   ########.fr       */
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

static void	def_pipe(t_matrix **temp_a, t_matrix **temp_b, int pipe, int cmmd)
{
	while ((*temp_b))
	{
		if ((*temp_b)->type == PIPE && (*temp_a)->type != MS_FILE && cmmd == 0
			&& (*temp_a)->type != GREATER && (*temp_a)->type != LESSER
			&& (*temp_a)->type != DOUBLEGREATER && (*temp_a)->type != DOUBLELESSER)
		{
			(*temp_b)->type = CMMND;
			pipe++;
			cmmd++;
		}
		else if ((*temp_a)->type == GREATER || (*temp_a)->type == LESSER
			|| (*temp_a)->type == DOUBLEGREATER || (*temp_a)->type == DOUBLELESSER)
			(*temp_b)->type = MS_FILE;
		else if ((*temp_a)->type == PIPE && (*temp_b)->type == WORD)
			(*temp_b)->type = CMMND;
		else if ((*temp_b)->type == WORD
				|| (*temp_b)->type == CMMND || (*temp_b)->type == MS_FILE)
			(*temp_b)->type = PARAM;
		(*temp_a) = (*temp_a)->next;
		(*temp_b) = (*temp_b)->next;
	}
}

static t_matrix	*define_word(t_matrix *lst)
{
	t_matrix	*temp;
	t_matrix	*temp2;
	t_matrix	*head;

	head = lst;
	temp = lst;
	temp2 = lst->next;
	if (temp->type == WORD && temp && temp2)
	{
		temp->type = CMMND;
		temp = temp->next;
		temp2 = temp2->next;
	}
	def_pipe(&temp, &temp2, 0, 0);
	return (head);
}

static t_matrix	*create_mtx(char *str)
{
	t_matrix	*ms;

	ms = malloc(sizeof(t_matrix));
	if (!ms)
		return (NULL);
	ms->str = ft_strdup(str);
	ms->type = search_type(str);
	ms->next = NULL;
	ms->prev = NULL;
	return (ms);
}

t_matrix	*parse_str(char *str)
{
	char		**parse_str;
	t_matrix	*mtx;
	t_matrix	*head;
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
