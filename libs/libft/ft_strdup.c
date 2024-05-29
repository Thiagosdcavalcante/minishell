/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:59:55 by tsantana          #+#    #+#             */
/*   Updated: 2023/10/18 21:27:54 by tsantana         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char		*new_arr;
	int			i;
	int			size;

	i = 0;
	size = ft_strlen(s);
	new_arr = (char *) malloc((size + 1) * sizeof(char));
	if (!new_arr)
		return (NULL);
	ft_memcpy((void *) new_arr, s, size);
	new_arr[size] = '\0';
	return (new_arr);
}
