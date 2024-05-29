/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:59:47 by tsantana          #+#    #+#             */
/*   Updated: 2024/05/29 15:12:32 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	counter;

	counter = 0;
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	else if (size == 2)
	{
		dst[counter] = src[counter];
		dst[counter + 1] = '\0';
	}
	else
	{
		while (counter < (size - 1) && src[counter] != '\0')
		{
			dst[counter] = src[counter];
			counter++;
		}
		dst[counter] = '\0';
	}
	return (src_len);
}
