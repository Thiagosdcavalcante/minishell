/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gambs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcarrara <vcarrara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 12:38:39 by alexandreju       #+#    #+#             */
/*   Updated: 2024/06/30 13:20:25 by vcarrara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	do_not_have(char *input)
{
	int	i;
	int	result;

	i = 0;
	result = 64;
	while (input[i])
	{
		if (input[i] != result)
		{
			i++;
		}
		else
		{
			i = 0;
			result++;
		}
	}
	return (result);
}

char	*set_spaces(char *input)
{
	char	*double_input;
	int		i;
	int		j;
	int		input_len;

	input_len = ft_strlen(input);
	double_input = (char *)ft_calloc((input_len * 2 + 1), sizeof(char));
	if (!double_input)
		return (NULL);
	i = 0;
	j = 0;
	while (i < input_len)
	{
		if (input[i] == '|')
		{
			double_input[j] = ' ';
			double_input[++j] = input[i];
			double_input[++j] = ' ';
			j++;
		}
		else
		{
			double_input[j] = input[i];
			j++;
		}
		i++;
	}
	double_input[j] = '\0';
	return (double_input);
}

char	**remove_wild_char(char **input, char wild_char)
{
	char	**result;
	int		i;
	int		j;

	i = ft_strlen_array(input);
	result = (char **)malloc((i + 1) * sizeof(char *));
	i = 0;
	while (input[i])
	{
		j = 0;
		result[i] = (char *)ft_calloc(sizeof(char*), (ft_strlen(input[i])) + 1);
		while (input[i][j] != '\0')
		{
			if (input[i][j] == wild_char)
				result[i][j] = ' ';
			else
				result[i][j] = input[i][j];
			j++;
		}
		result[i][j] = '\0';
		i++;
	}
	result[i] = NULL;
	return (result);
}

char	*set_wild_char(char *input, char wild_char)
{
	int		i;
	int		j;
	char	*input_wild;
	int		quote;

	input_wild = ft_calloc(sizeof(char*), ft_strlen(input));
	quote = 0;
	i = 0;
	j = 0;
	while (input[i] != '\0')
	{
		if (input[i] == 34 && quote++ > 0)
			quote = 0;
		if (input[i] == ' ' && quote == 1)
		{
			input_wild[i] = wild_char;
			i++;
		}
		else
		{
			input_wild[i] = input[i];
			i++;
		}
	}
	input_wild[i] = '\0';
	return (input_wild);
}

void	free_gambs(char **input)
{
	int	i;

	i = 0;
	while (input[i])
		free(input[i++]);
}
