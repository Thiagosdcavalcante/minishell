/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:27:01 by ajuliao-          #+#    #+#             */
/*   Updated: 2023/11/04 14:57:22 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result;
	int		i;
	int		len_s;

	len_s = ft_strlen(s);
	if (!s && !f)
		return (0);
	if (len_s == 0)
		return (ft_strdup(""));
	i = 0;
	result = (char *) malloc(sizeof(char) * len_s + 1);
	if (result == 0)
		return (0);
	while (s[i] != '\0')
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
