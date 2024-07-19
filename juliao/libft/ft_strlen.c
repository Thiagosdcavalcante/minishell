/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandrejuliao <alexandrejuliao@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:08:00 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/06/22 18:07:01 by alexandreju      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

size_t	ft_strlen_array(char **str)
{
	size_t	len;

	len = 0;
	while (str[len] != NULL)
		len++;
	return (len);
}
