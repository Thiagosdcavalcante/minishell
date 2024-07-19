/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 20:54:37 by ajuliao-          #+#    #+#             */
/*   Updated: 2023/11/13 10:51:44 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	f;

	i = 0;
	f = 0;
	if (!*little || big == little)
		return ((char *)big);
	if (len == 0)
		return (0);
	while (big[i] && i < len)
	{
		f = 0;
		while (big[i + f] == little[f] && big[i + f] && little[f] != '\0'
			&& (i + f) < len)
			f++;
		if (f == (size_t)ft_strlen(little))
			return ((char *)big + i);
		i++;
	}
	return (0);
}
