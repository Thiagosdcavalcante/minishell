/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:59:05 by ajuliao-          #+#    #+#             */
/*   Updated: 2023/11/09 22:49:59 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*node;

	if (!del && !lst)
		return ;
	while (*lst)
	{
		del((*lst)->content);
		node = *lst;
		*lst = node->next;
		free(node);
	}
	*lst = NULL;
}
