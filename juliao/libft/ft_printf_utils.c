/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 19:52:45 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/03/16 10:37:35 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_hexa(unsigned long long n, char c)
{
	int		count;
	char	*hexa;

	if (c == 'x')
		hexa = "0123456789abcdef";
	else
		hexa = "0123456789ABCDEF";
	if (n < 16)
		return (put_char(hexa[n]));
	else
	{
		count = get_hexa(n / 16, c);
		return (count + get_hexa(n % 16, c));
	}
}

int	get_pointer(unsigned long int pointer)
{
	unsigned long long	my_pointer;
	int					count;

	my_pointer = (unsigned long int)pointer;
	count = 0;
	if (pointer == 0)
	{
		count += put_str("(nil)");
		return (count);
	}
	put_char('0');
	put_char('x');
	count += get_hexa(my_pointer, 'x');
	return (count + 2);
}

int	put_char(int c)
{
	write(1, &c, 1);
	return (1);
}

int	put_str(char *str)
{
	int	len;

	len = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return (len + 6);
	}
	while (*str)
	{
		put_char(*str++);
		len++;
	}
	return (len);
}
