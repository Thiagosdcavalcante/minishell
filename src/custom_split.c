/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:14:26 by tsantana          #+#    #+#             */
/*   Updated: 2024/07/05 18:11:50 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static int	ms_count_words(const char *s, const char c)
{
	int	count;
	int	index;

	count = 0;
	index = 0;
	if (ft_strlen(s) == 0)
		return (0);
	while (s[index] != '\0')
	{
		if (s[index] != (unsigned char) c)
		{
			while (s[index] != (unsigned char)c && s[index] != '\0')
				index++;
			count++;
		}
		if (s[index] != '\0')
			index++;
	}
	return (count);
}

static char	find_quote(char quote, const char *s, int i)
{
	if (!quote && ft_strchr("\'\"", s[i]))
		quote = s[i];
	else if (quote && s[i] == quote)
		quote = 0;
	return (quote);
}

static void	ms_fill_arr(int size, const char *s, const char c, char ***str_list)
{
	int	quote;
	int	counter;
	int	i;
	int	j;

	i = 0;
	quote = 0;
	counter = 0;
	while (s[i] != '\0' && counter < size)
	{
		j = 0;
		while (s[i] == c)
			i++;
		while (s[i + j] && (quote || s[i + j] != c))
		{
			quote = find_quote(quote, s, i + j);
			j++;
		}
		(*str_list)[counter] = ft_substr(&s[i], 0, j);
		counter++;
		i += j;
	}
	(*str_list)[size] = 0;
}

char	**custom_split(char const *s, char c)
{
	int		size;
	char	**str_list;

	size = ms_count_words(s, c);
	if (size == 0)
		return (ft_calloc(1, sizeof(char *)));
	str_list = (char **) ft_calloc((size + 1), sizeof(char *));
	if (str_list == 0)
		return (0);
	ms_fill_arr(size, s, c, &str_list);
	return (str_list);
}
