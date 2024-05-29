/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 15:26:58 by tsantana          #+#    #+#             */
/*   Updated: 2023/10/30 21:20:27 by tsantana         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, const char c)
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

void	fill_arr(int size, const char *s, const char c, char ***str_list)
{
	int	counter;
	int	i;
	int	j;

	i = 0;
	counter = 0;
	while (s[i] != '\0' && counter < size)
	{
		j = 0;
		while (s[i] == c)
			i++;
		while (s[i + j] && s[i + j] != c)
			j++;
		(*str_list)[counter] = ft_substr(&s[i], 0, j);
		counter++;
		i += j;
	}
	(*str_list)[size] = 0;
}

char	**ft_split(char const *s, char c)
{
	int		size;
	char	**str_list;

	size = count_words(s, c);
	if (size == 0)
		return (ft_calloc(1, sizeof(char *)));
	str_list = (char **) ft_calloc((size + 1), sizeof(char *));
	if (str_list == 0)
		return (0);
	fill_arr(size, s, c, &str_list);
	return (str_list);
}
