/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 21:34:03 by tsantana          #+#    #+#             */
/*   Updated: 2023/10/18 21:57:49 by tsantana         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*new_arr;
	unsigned int	size;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_arr = (char *)ft_calloc(size, sizeof(char));
	if (new_arr == NULL)
		return (NULL);
	ft_strlcpy(new_arr, s1, ft_strlen(s1) + 1);
	ft_strlcat(new_arr, s2, size);
	return (new_arr);
}
