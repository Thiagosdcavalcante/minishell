/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:22:19 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/06/20 20:33:44 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;

	if (len == 0 || start >= ft_strlen(s))
	{
		result = malloc(1);
		if (result == 0)
			return (0);
		result[0] = '\0';
		return (result);
	}
	if (len >= (size_t)ft_strlen(s))
		result = (char *) malloc(sizeof(char) * (ft_strlen(s) - start) + 1);
	else
		result = (char *) malloc(sizeof(char) * len + 1);
	if (result == 0)
		return (0);
	i = 0;
	while ((start + i) < (size_t)ft_strlen(s) && i < len)
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
