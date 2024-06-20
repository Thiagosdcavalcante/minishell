/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpiana <erpiana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 20:08:25 by tsantana          #+#    #+#             */
/*   Updated: 2024/06/20 19:22:57 by erpiana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <strings.h>

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
