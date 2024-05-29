/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:24:53 by tsantana          #+#    #+#             */
/*   Updated: 2024/05/29 18:00:07 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <readline/history.h>
#include <stdlib.h>

static void	free_split(char **split)
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

static t_matrix	*create_mtx(char *str)
{
	t_matrix	*ms;

	ms = malloc(sizeof(t_matrix));
	if (!ms)
		return (NULL);
	ms->str = ft_strdup(str);
	ms->type = search_type(str);
	ms->next = NULL;
	return (ms);
}

static t_matrix	*parse_str(char *str)
{
	char		**parse_str;
	t_matrix	*mtx;
	t_matrix	*head;
	int			i;

	if (!str)
		return (NULL);
	i = 0;
	mtx = NULL;
	parse_str = ft_split(str, ' ');
	mtx = create_mtx(parse_str[i]);
	if (!mtx)
		return (NULL);
	head = mtx;
	i++;
	while (parse_str[i])
	{
		mtx->next = create_mtx(parse_str[i]);
		mtx = mtx->next;
		i++;
	}
	free_split(parse_str);
	return (head);
}

static void	print_mtx(t_matrix *mtx)
{
	while (mtx)
	{
		ft_printf("%s - TOKEN: %d\n", mtx->str, mtx->type);
		mtx = mtx->next;
	}
}

int	main(void)
{
	t_mini	mini;

	mini = (t_mini){0};
	mini.cmmds = NULL;
	while (1)
	{
		mini.in_ms = readline("minishell");
		if (!mini.in_ms)
			exit(EXIT_SUCCESS);
		if (mini.in_ms[0] != '\0')
		{
			ft_printf("%s\n", mini.in_ms);
			mini.cmmds = parse_str(mini.in_ms);
			print_mtx(mini.cmmds);
		}
		final_free(&mini);
	}
	return (0);
}
