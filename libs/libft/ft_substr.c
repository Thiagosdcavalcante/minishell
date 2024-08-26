/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:25:07 by tsantana          #+#    #+#             */
/*   Updated: 2024/08/24 17:30:49 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*new_arr;
	unsigned int	size_s;

	if (!s)
		return (0);
	size_s = ft_strlen(s);
	if (start >= size_s)
		return (ft_strdup(""));
	if ((size_s - start) < len)
		len = size_s - start;
	new_arr = (char *) malloc((len + 1) * sizeof(char));
	if (!new_arr)
		return (0);
	ft_strlcpy(new_arr, s + start, len + 1);
	return (new_arr);
}
