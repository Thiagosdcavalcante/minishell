/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 23:47:41 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/03/16 10:37:49 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	if (c == '\0')
		return (1);
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			words++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (words);
}

static char	*add_words(const char *s, int start, int end)
{
	char	*words;
	int		i;

	i = 0;
	words = malloc(sizeof(char) * (end - start + 1));
	if (!words)
		return (NULL);
	while (start < end)
		words[i++] = s[start++];
	words[i] = '\0';
	return (words);
}

char	**ft_split(char const *s, char c)
{
	size_t		i;
	int			j;
	int			start;
	char		**result;

	i = 0;
	j = 0;
	start = -1;
	result = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!s || !result)
		return (0);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && start < 0)
			start = i;
		else if ((s[i] == c || i == ft_strlen(s)) && start >= 0)
		{
			result[j++] = add_words(s, start, i);
			start = -1;
		}
		i++;
	}
	result[j] = 0;
	return (result);
}
