/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:25:07 by tsantana          #+#    #+#             */
/*   Updated: 2023/10/30 21:22:04 by tsantana         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*new_arr;
	unsigned int	size_s;
	unsigned int	i;

	i = 0;
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
