/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:46:28 by tsantana          #+#    #+#             */
/*   Updated: 2023/10/17 20:57:56 by tsantana         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total_size;
	void	*ptr;

	total_size = nmemb * size;
	ptr = (void *)malloc(total_size * sizeof(*ptr));
	if (ptr == NULL)
		return (NULL);
	return (ft_memset(ptr, 0, total_size));
}
