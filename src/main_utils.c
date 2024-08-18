/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:55:51 by tsantana          #+#    #+#             */
/*   Updated: 2024/08/18 14:38:43 by tsantana         ###   ########.fr       */
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

t_bool	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (TRUE);
	else
		return (FALSE);
}
