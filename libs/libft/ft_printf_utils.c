/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:52:40 by tsantana          #+#    #+#             */
/*   Updated: 2024/04/05 22:28:15 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	pf_str_to_list(char *src, t_pf_list **list)
{
	if (!src)
		pf_str_to_list("(null)", list);
	while (src && *src)
		pf_ft_lstadd_back(&(*list), pf_ft_lstnew(*src++));
}

void	pf_ft_put_address(unsigned long int address, t_pf_list **list)
{
	if (!address)
	{
		pf_str_to_list("(nil)", list);
		return ;
	}
	pf_ft_lstadd_back(list, pf_ft_lstnew('0'));
	pf_ft_lstadd_back(list, pf_ft_lstnew('x'));
	pf_putnbr_convert(address, list, "0123456789abcdef");
}

void	pf_ft_putnumb(unsigned long n, t_pf_list **list)
{
	unsigned long	num;

	num = (unsigned long)n;
	if (num <= 9)
		pf_ft_lstadd_back(&(*list), pf_ft_lstnew(num + '0'));
	if (num >= 10)
	{
		pf_ft_putnumb((num / 10), &(*list));
		pf_ft_putnumb((num % 10), &(*list));
	}
}

t_pf_list	*pf_ft_lstnew(char content)
{
	t_pf_list	*node;

	node = malloc(sizeof(t_pf_list));
	if (node == NULL)
		return (NULL);
	node->character = content;
	node->next = NULL;
	return (node);
}

void	pf_ft_lstadd_back(t_pf_list **lst, t_pf_list *pf_new)
{
	t_pf_list	*temp;

	if (!lst || !pf_new)
		return ;
	temp = *lst;
	if (!*lst)
		*lst = pf_new;
	else
	{
		while (temp -> next)
			temp = temp->next;
		temp -> next = pf_new;
	}
}
