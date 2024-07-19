/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:03:07 by alejuliao         #+#    #+#             */
/*   Updated: 2024/03/16 10:37:39 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_number(char var_print, int ap)
{
	char	*var_itoa;
	int		len;

	len = 0;
	if (var_print == 'd' || var_print == 'i')
	{
		var_itoa = ft_itoa(ap);
		len += put_str(var_itoa);
		free(var_itoa);
	}
	if (var_print == 'u')
	{
		var_itoa = ft_itoa_u(ap);
		len += put_str(var_itoa);
		free(var_itoa);
	}
	return (len);
}

int	what_format(char var_print, va_list ap)
{
	int		len;

	len = 0;
	if (var_print == 'c')
		len += put_char(va_arg(ap, int));
	if (var_print == 's')
		len += put_str(va_arg(ap, char *));
	if (var_print == 'd' || var_print == 'i' || var_print == 'u')
		len += is_number(var_print, va_arg(ap, int));
	if (var_print == 'p')
		len += get_pointer(va_arg(ap, unsigned long int ));
	if (var_print == 'x')
		len += get_hexa((long)va_arg(ap, unsigned int), 'x');
	if (var_print == 'X')
		len += get_hexa((long)va_arg(ap, unsigned int), 'X');
	if (var_print == '%')
		len += put_char(37);
	return (len);
}

int	ft_printf(const char *var_print, ...)
{
	va_list	ap;
	int		len;

	va_start(ap, var_print);
	len = 0;
	if (var_print == NULL)
		return (-1);
	while (*var_print != '\0')
	{
		if (*var_print == '%')
			len += what_format(*++var_print, ap);
		else
			len += write(1, var_print, 1);
		++var_print;
	}
	va_end(ap);
	return (len);
}
