/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:37:34 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/03/30 15:22:54 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_c(char c, const char *set)
{
	int	i;

	i = 0;
	if (!*set)
		return (0);
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*res;
	unsigned int	len_s1;
	unsigned int	start;
	unsigned int	end;

	len_s1 = (unsigned int)ft_strlen(s1);
	start = 0;
	end = 0;
	while (count_c(s1[start], set) == 1)
		start++;
	if (start == len_s1)
	{
		res = ft_strdup("");
		return (res);
	}
	while (count_c(s1[len_s1 - end - 1], set) == 1)
		end++;
	res = ft_substr(s1, start, len_s1 - start - end);
	return (res);
}
