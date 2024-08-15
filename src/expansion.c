/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 15:56:40 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/08/15 15:28:25 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expansion(t_mini *data, char *arg)
{
	int		j;
	char	*result;
	char	*key;

	j = 0;
	while (arg[j + 1] != ' ' && arg[j + 1] != '"' && arg[j + 1] != '\0' )
		j++;
	key = ft_substr(arg, 1, j);
	result = get_env(data, key);
	free(key);
	return (result);
}

char	*full_expansion(t_mini *data, char *arg)
{
	int		i;
	int		j;
	char	*result;

	i = -1;
	j = 0;
	result = ft_strdup("");
	while (arg[++i])
	{
		if (arg[i] == '$' && (arg[i + 1] != '$'
				&& arg[i + 1] != ' ' && arg[i + 1] != '\0'))
		{
			j = i + 1;
			while (arg[j] != ' ' && arg[j] != '"' && arg[j] != '\0')
				j++;
			utils_expansion2(data, &arg, i, j, &result);
			i = j - 1;
		}
		else
			utils_expansion3(&result, arg, i);
	}
	return (result);
}

void	init_expansion(t_mini *data, char **args)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (args[++i])
	{
		j = 0;
		if (args[i][j] == '\'')
		{
			temp = ft_substr(args[i], 1, ft_strlen(args[i]) - 2);
			free(args[i]);
			args[i] = temp;
		}
		else if (args[i][j] == '"')
			utils_expansion(data, &args[i]);
		else if (args[i][j] == '$')
		{
			temp = expansion(data, args[i]);
			free(args[i]);
			args[i] = ft_calloc(1, ft_strlen(temp) + 1);
			ft_strcpy(args[i], temp);
			free(temp);
		}
	}
}
