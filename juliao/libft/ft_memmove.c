/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:38:38 by ajuliao-          #+#    #+#             */
/*   Updated: 2023/11/04 08:38:15 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = n;
	if (dest == 0 && src == 0)
		return (0);
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	while (i--)
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
	return (dest);
}
