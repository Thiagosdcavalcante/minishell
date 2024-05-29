/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:30:47 by tsantana          #+#    #+#             */
/*   Updated: 2023/10/20 18:02:32 by tsantana         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if ((unsigned char)*s == (unsigned char) c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char) c == '\0')
		return ((char *) s);
	return (NULL);
}
