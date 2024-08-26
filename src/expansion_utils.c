/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 13:52:03 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/08/26 13:39:43 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strcpy(char *dst, const char *src)
{
	if (src && dst)
	{
		while (*src)
			*dst++ = *src++;
		*dst = '\0';
	}
}

char	*expansion(t_mini *data, char *arg)
{
	int		j;
	char	*result;
	char	*key;

	j = 0;
	if (!arg || !*arg)
		return (ft_strdup(""));
	if (arg[0] == '$' && arg[1] == '?')
		return (ft_strjoin(ft_itoa(data->status), &arg[2]));
	if (arg[0] == '$' && arg[1] == '\0')
		return (ft_strdup("$"));
	while (arg[j + 1] != ' ' && arg[j + 1] != '"' && arg[j + 1] != '\0' )
		j++;
	key = ft_substr(arg, 1, j);
	result = get_env(data, key);
	free(key);
	if (result)
		return (ft_strdup(result));
	return (ft_strdup(""));
}

void	one_quote(char **arg, int *i, char **new_result, char **result)
{
	char	*temp;
	int		start;

	start = ++(*i);
	while ((*arg)[*i] && (*arg)[*i] != '\'')
		(*i)++;
	temp = ft_substr(*arg, start, *i - start);
	*new_result = ft_strjoin(*result, temp);
	free(*result);
	free(temp);
	*result = *new_result;
}

void	handle_var_expansion(t_mini *data, char *arg, int *i, char **result)
{
	char	*temp;
	char	*expanded_var;
	char	*new_result;
	int		j;

	j = *i + 1;
	while (arg[j] && arg[j] != '"' && arg[j] != ' '
		&& arg[j] != '$' && arg[j] != '\'')
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
	*i = j - 1;
}

void	handle_normal_char(char c, char **result)
{
	char	*new_char;
	char	*new_result;

	new_char = (char *)malloc(2 * sizeof(char));
	if (!new_char)
		return ;
	new_char[0] = c;
	new_char[1] = '\0';
	new_result = ft_strjoin(*result, new_char);
	free(*result);
	free(new_char);
	*result = new_result;
}
