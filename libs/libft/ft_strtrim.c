/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:54:12 by tsantana          #+#    #+#             */
/*   Updated: 2023/11/08 21:36:05 by tsantana         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	int	i;
	int	counter;

	counter = 0;
	if (ft_strlen(s1) == 0 || ft_strlen(set) == 0)
		return (ft_substr(s1, 0, ft_strlen(s1)));
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	i = ft_strlen(s1);
	while (*s1 && ft_strchr(set, s1[i]))
	{
		i--;
		counter++;
	}
	return (ft_substr(s1, 0, ft_strlen(s1) - counter + 1));
}
