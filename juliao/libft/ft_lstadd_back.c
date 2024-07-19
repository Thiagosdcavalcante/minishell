/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:25:58 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/06/08 12:50:56 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*swap;

	if (!new || !lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	swap = *lst;
	while (swap->next)
		swap = swap->next;
	swap->next = new;
}
