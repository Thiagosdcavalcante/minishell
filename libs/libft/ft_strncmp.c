/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:15:10 by tsantana          #+#    #+#             */
/*   Updated: 2023/10/15 20:17:57 by tsantana         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ptr_s1;
	unsigned char	*ptr_s2;

	i = 0;
	ptr_s1 = (unsigned char *) s1;
	ptr_s2 = (unsigned char *) s2;
	while (i < n && ptr_s1[i] != '\0'
		&& ptr_s2[i] != '\0' && ptr_s1[i] == ptr_s2[i])
		i++;
	if (n != i)
		return (ptr_s1[i] - ptr_s2[i]);
	return (0);
}
