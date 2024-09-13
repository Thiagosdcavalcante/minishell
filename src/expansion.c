/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 15:56:40 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/09/12 22:23:27 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	double_quote_expansion(t_mini *data, char *arg, int *i, char **result)
{
	(*i)++;
	while (arg[*i] && arg[*i] != '"')
	{
		if (arg[*i] == '$')
		{
			handle_var_expansion(data, arg, i, result);
			if (!*result)
				return ;
		}
		else
		{
			handle_normal_char(arg[*i], result);
			if (!*result)
				return ;
		}
		(*i)++;
	}
}

void	expand_variable(t_mini *data, char *arg, int *i, char **result)
{
	int		j;
	char	*temp;
	char	*expanded_var;
	char	*new_result;

	j = *i + 1;
	while (arg[j] && arg[j] != ' ' && arg[j] != '"'
		&& arg[j] != '\'' && arg[j] != '$')
		j++;
	temp = ft_substr(arg, *i, j - *i);
	expanded_var = expansion(data, temp);
	free(temp);
	if (!expanded_var)
		expanded_var = ft_strdup("");
	new_result = ft_strjoin(*result, expanded_var);
	free(*result);
	free(expanded_var);
	*result = new_result;
	if (!*result)
		return ;
	*i = j - 1;
}

void	handle_expansion_case(t_mini *data, char *arg, int *i, char **result)
{
	if (arg[*i] == '"')
		double_quote_expansion(data, arg, i, result);
	else if (arg[*i] == '$')
		expand_variable(data, arg, i, result);
	else
		handle_normal_char(arg[*i], result);
}

char	*full_expansion(t_mini *data, char *arg)
{
	int		i;
	char	*result;
	char	*new_result;

	i = 0;
	result = ft_strdup("");
	while (arg[i])
	{
		if (arg[i] == '\'')
		{
			one_quote(&arg, &i, &new_result, &result);
			if (!result)
				return (NULL);
		}
		else
		{
			handle_expansion_case(data, arg, &i, &result);
			if (!result)
				return (NULL);
		}
		i++;
	}
	return (result);
}

void	init_expansion(t_mini *data, char **args, char **n_args)
{
	int		i;
	char	*temp;

	i = 0;
	while (args[i])
	{
		temp = full_expansion(data, args[i]);
		if (temp != NULL)
		{
			n_args[i] = ft_strdup(temp);
			free(temp);
		}
		else
			n_args[i] = ft_strdup(args[i]);
		i++;
	}
	n_args[i] = NULL;
}
