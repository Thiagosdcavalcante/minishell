/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:15:07 by ajuliao-          #+#    #+#             */
/*   Updated: 2023/10/28 13:09:07 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*valuedest;
	char	*valuesrc;

	valuedest = (char *)dest;
	valuesrc = (char *)src;
	i = 0;
	if (dest == 0 && src == 0)
		return (0);
	while (i < n)
	{
		valuedest[i] = valuesrc[i];
		i++;
	}
	return (dest);
}
