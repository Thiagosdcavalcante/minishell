/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:35:01 by tsantana          #+#    #+#             */
/*   Updated: 2023/11/06 18:39:08 by tsantana         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*pnt_src;
	unsigned char	*pnt_dest;

	pnt_src = (unsigned char *)src;
	pnt_dest = (unsigned char *)dest;
	if (!pnt_src && !pnt_dest)
		return (NULL);
	else if (dest < src)
		return (ft_memcpy(dest, src, n));
	else if (n > 0)
		while (n--)
			pnt_dest[n] = pnt_src[n];
	return (dest);
}
