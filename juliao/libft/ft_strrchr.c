/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:36:32 by ajuliao-          #+#    #+#             */
/*   Updated: 2023/11/13 09:52:03 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		result;

	result = -1;
	i = 0;
	if ((char)c == '\0')
		return (&(((char *)s)[ft_strlen(s)]));
	while (s[i])
	{
		if (s[i] == (char)c)
			result = i;
		i++;
	}
	if (result >= 0)
		return (&(((char *)s)[result]));
	return (NULL);
}
