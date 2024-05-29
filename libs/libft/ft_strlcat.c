/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:32:51 by tsantana          #+#    #+#             */
/*   Updated: 2023/11/06 19:23:44 by tsantana         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	result;

	i = 0;
	while (dst[i] != '\0')
		i++;
	if (i >= size)
		return (ft_strlen(src) + size);
	while (i < (size - 1) && *src)
	{
		dst[i] = *src;
		i++;
		src++;
	}
	dst[i] = '\0';
	result = ft_strlen(dst) + ft_strlen(src);
	return (result);
}
