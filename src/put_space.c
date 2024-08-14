/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:56:36 by tsantana          #+#    #+#             */
/*   Updated: 2024/08/14 14:56:43 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	aux_cond(char *str, char *dest, int *i, int *j)
{
	if (aux_parse(str[(*i) + 1]) == 2 && (str[(*i)] == str[(*i) + 1]))
	{
		dest[(*j)++] = ' ';
		dest[(*j)++] = str[(*i)++];
		dest[(*j)++] = str[(*i)];
		dest[(*j)++] = ' ';
		(*i)++;
	}
	else
	{
		dest[(*j)++] = ' ';
		dest[(*j)++] = str[(*i)];
		dest[(*j)++] = ' ';
		(*i)++;
	}
}

static char	*str_new(char *str, int extra)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = malloc((ft_strlen(str) + (2 * extra) + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] && str[i + 1] && aux_parse(str[i]) == 2)
			aux_cond(str, new_str, &i, &j);
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char	*put_space_ms(char *str)
{
	int		i;
	int		space;

	i = 0;
	space = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (aux_parse(str[i]) == 2)
			space++;
		i++;
	}
	return (str_new(str, space));
}
