/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:55:51 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/14 18:54:26 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	aux_parse(char letter)
{
	if (letter == ' ')
		return (1);
	if (letter == '|' || letter == '&' || letter == '<' || letter == '>')
		return (2);
	return (0);
}

int	size_str(char *str)
{
	int		i;

	i = 0;
	while (str[i] && aux_parse(str[i]) == 0)
		i++;
	return (i);
}

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (TRUE);
	else
		return (FALSE);
}

int	tokens_checker(t_mini *mini)
{
	t_tokens	*check;

	if (is_file(mini->cmmds->type) == TRUE)
		if (verify_if_is_only_one_sinal(mini) != 0)
			return (1);
	check = mini->cmmds;
	while (check)
	{
		if (is_file(check->type) == TRUE
			&& is_file(check->next->type) == TRUE)
		{
			cond_minishell(&mini, 4);
			return (1);
		}
		if ((is_file(check->type) == TRUE && check->next->type == PIPE)
			|| (check->type == PIPE && !check->next))
		{
			cond_minishell(&mini, 4);
			return (1);
		}
		check = check->next;
	}
	return (0);
}
