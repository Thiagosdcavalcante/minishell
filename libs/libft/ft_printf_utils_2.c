/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:05:10 by tsantana          #+#    #+#             */
/*   Updated: 2024/04/07 16:07:25 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	pf_putnbr_convert(unsigned long int numb, t_pf_list **list, char *hexas)
{
	if (numb <= 15)
		pf_ft_lstadd_back(list, pf_ft_lstnew(hexas[numb]));
	if (numb >= 16)
	{
		pf_putnbr_convert((numb / 16), list, hexas);
		pf_putnbr_convert((numb % 16), list, hexas);
	}
}
