/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 21:44:45 by ajuliao-          #+#    #+#             */
/*   Updated: 2023/11/04 09:04:43 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*cs1;
	unsigned char	*cs2;

	if (n < 1)
		return (0);
	i = 0;
	cs1 = (unsigned char *)s1;
	cs2 = (unsigned char *)s2;
	while (*cs1 == *cs2 && i < n - 1)
	{
		i++;
		cs1++;
		cs2++;
	}
	return (*cs1 - *cs2);
}
