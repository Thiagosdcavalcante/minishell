/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:24:49 by tsantana          #+#    #+#             */
/*   Updated: 2023/11/04 19:06:56 by tsantana         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	num;

	num = (long)n;
	if (num < 0)
	{
		num = num * (-1);
		ft_putchar_fd('-', fd);
	}
	if (num <= 9)
		ft_putchar_fd((num + '0'), fd);
	if (num >= 10)
	{
		ft_putnbr_fd((num / 10), fd);
		ft_putnbr_fd((num % 10), fd);
	}
}
