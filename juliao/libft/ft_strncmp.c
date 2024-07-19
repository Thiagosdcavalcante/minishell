/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:45:04 by ajuliao-          #+#    #+#             */
/*   Updated: 2023/11/04 09:03:59 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	if (n < 1)
		return (0);
	i = 0;
	while (*ptr1 == *ptr2 && *ptr1 && i < n - 1)
	{
		ptr1++;
		ptr2++;
		i++;
	}
	return (*ptr1 - *ptr2);
}
