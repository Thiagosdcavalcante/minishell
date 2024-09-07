/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:56:36 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/06 16:57:28 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_quote(char letter, int *quote, int *quote_d)
{
	if (letter == '\'' && *quote_d == 0)
	{
		*quote = !(*quote);
		return (1);
	}
	else if (letter == '\"' && *quote == 0)
	{
		*quote_d = !(*quote_d);
		return (1);
	}
	return (0);
}

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

static char	*str_new(char *str, int extra, int quote, int quote_d)
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
		if (!is_quote(str[i], &quote, &quote_d))
		{
			if (str[i] && str[i + 1] && aux_parse(str[i]) == 2
				&& quote == 0 && quote_d == 0)
				aux_cond(str, new_str, &i, &j);
			else
				new_str[j++] = str[i++];
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char	*put_space_ms(char *str)
{
	int	i;
	int	space;
	int	quote;
	int	quote_d;

	i = 0;
	space = 0;
	quote = 0;
	quote_d = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		is_quote(str[i], &quote, &quote_d);
		if (aux_parse(str[i]) == 2 && quote == 0 && quote_d == 0)
			space++;
		i++;
	}
	return (str_new(str, space, quote, quote_d));
}
