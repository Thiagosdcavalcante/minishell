/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:28:33 by ajuliao-          #+#    #+#             */
/*   Updated: 2023/11/04 15:58:14 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;
	unsigned int	len_s;

	if (!s && !f)
		return ;
	i = 0;
	len_s = ft_strlen(s);
	while (i < len_s)
	{
		f(i, &s[i]);
		i++;
	}
}
