/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:15:47 by tsantana          #+#    #+#             */
/*   Updated: 2024/05/14 15:25:14 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (s == 0)
		ft_putchar_fd('\n', fd);
	else
	{
		ft_putstr_fd(s, fd);
		ft_putchar_fd('\n', fd);
	}
}
