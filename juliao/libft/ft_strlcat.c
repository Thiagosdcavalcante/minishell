/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:13:26 by ajuliao-          #+#    #+#             */
/*   Updated: 2023/11/04 12:47:43 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_src;
	char	*str;

	str = (char *)src;
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(str);
	if (!size)
		return (len_src);
	if (len_dst < size)
	{
		ft_strlcpy(dst + len_dst, src, size - len_dst);
		return (len_dst + len_src);
	}
	return (len_src + size);
}
