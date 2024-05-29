/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:21:54 by tsantana          #+#    #+#             */
/*   Updated: 2024/05/22 15:03:08 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(char))
{
	t_list	*temp;
	t_list	*add_next;

	if (lst)
	{
		temp = *lst;
		while (temp)
		{
			add_next = temp->next;
			ft_lstdelone(temp, del);
			temp = add_next;
		}
		*lst = NULL;
	}
}
