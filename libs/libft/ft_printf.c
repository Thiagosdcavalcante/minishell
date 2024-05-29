/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 19:12:52 by tsantana          #+#    #+#             */
/*   Updated: 2024/04/13 22:17:24 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_result(t_pf_list **list)
{
	t_pf_list	*temp;
	int			counter;

	temp = *list;
	counter = 0;
	while (*list)
	{
		write (1, &(temp)->character, 1);
		counter++;
		*list = (*list)->next;
		free(temp);
		temp = *list;
	}
	return (counter);
}

static void	ft_putnbr(int n, t_pf_list **list)
{
	long	num;

	num = (long)n;
	if (num < 0)
	{
		num = num * (-1);
		pf_ft_lstadd_back(&(*list), pf_ft_lstnew('-'));
	}
	if (num <= 9)
		pf_ft_lstadd_back(&(*list), pf_ft_lstnew(num + '0'));
	if (num >= 10)
	{
		ft_putnbr((num / 10), &(*list));
		ft_putnbr((num % 10), &(*list));
	}
}

static void	custom_sc(t_pf_list **list, va_list args, char c)
{
	int	count;

	count = 0;
	if (!args)
		return ;
	else if (c == '%')
		pf_ft_lstadd_back(&(*list), pf_ft_lstnew('%'));
	else if (c == 'c')
		pf_ft_lstadd_back(&(*list), pf_ft_lstnew(va_arg(args, int)));
	else if (c == 's')
		pf_str_to_list(va_arg(args, char *), list);
	else if (c == 'd' || c == 'i')
		ft_putnbr(va_arg(args, int), list);
	else if (c == 'u')
		pf_ft_putnumb(va_arg(args, unsigned int), list);
	else if (c == 'p')
		pf_ft_put_address(va_arg(args, unsigned long int), list);
	else if (c == 'x')
		pf_putnbr_convert(va_arg(args, unsigned int), list, "0123456789abcdef");
	else if (c == 'X')
		pf_putnbr_convert(va_arg(args, unsigned int), list, "0123456789ABCDEF");
}	

int	ft_printf(const char *str, ...)
{
	t_pf_list	*list;
	va_list		args;

	list = NULL;
	if (!str)
		return (-1);
	va_start (args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			custom_sc(&list, args, *str);
		}
		else
			pf_ft_lstadd_back(&list, pf_ft_lstnew(*str));
		str++;
	}
	va_end (args);
	return (print_result(&list));
}
