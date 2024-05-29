/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:36:31 by tsantana          #+#    #+#             */
/*   Updated: 2023/10/15 18:27:34 by tsantana         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dst;
	unsigned char	*str;
	size_t			i;

	i = 0;
	dst = (unsigned char *)dest;
	str = (unsigned char *)src;
	if (dst == str)
		return (dest);
	while (i < n)
	{
		dst[i] = str[i];
		i++;
	}
	return (dst);
}
