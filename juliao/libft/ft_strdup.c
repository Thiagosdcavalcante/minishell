/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 10:39:41 by ajuliao-          #+#    #+#             */
/*   Updated: 2023/11/09 19:18:03 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*copy;
	int		len;

	len = 0;
	while (src[len] != '\0')
		len++;
	copy = (char *) malloc(sizeof(char) * len + 1);
	if (copy == 0)
		return (0);
	len = 0;
	while (src[len])
	{
		copy[len] = src[len];
		len++;
	}
	copy[len] = '\0';
	return (copy);
}
