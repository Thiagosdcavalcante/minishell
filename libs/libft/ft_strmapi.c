/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:11:55 by tsantana          #+#    #+#             */
/*   Updated: 2023/11/04 17:11:43 by tsantana         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned char	*string;
	unsigned int	size;
	unsigned int	count;

	size = ft_strlen(s);
	string = ft_calloc(size + 1, sizeof(unsigned char));
	if (string == NULL)
		return (NULL);
	count = 0;
	while (count < size)
	{
		string[count] = (*f)(count, s[count]);
		count++;
	}
	return ((char *)string);
}
