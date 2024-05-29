/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:01:14 by tsantana          #+#    #+#             */
/*   Updated: 2023/11/06 19:16:38 by tsantana         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	if ((unsigned char) c == '\0')
		return ((char *) &s[i]);
	while (i > 0)
	{
		if (s[i - 1] == (unsigned char) c)
			return ((char *) &s[i - 1]);
		i--;
	}
	return (NULL);
}
