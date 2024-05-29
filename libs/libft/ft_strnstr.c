/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 20:23:44 by tsantana          #+#    #+#             */
/*   Updated: 2023/11/05 17:36:11 by tsantana         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	if (!(*little))
		return ((char *) big);
	while (i <= len && len >= 0 && big[i] != '\0')
	{
		if (i + ft_strlen(little) > len)
			return (NULL);
		if (big[i] == little[0])
			if (ft_strncmp(&big[i], &little[0], ft_strlen(little)) == 0
				&& (ft_strlen(little) + i) <= len)
				return ((char *)&big[i]);
		i++;
	}
	return (0);
}
