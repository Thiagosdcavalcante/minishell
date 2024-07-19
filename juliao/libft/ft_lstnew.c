/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:55:46 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/06/24 17:57:24 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *) malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = (NULL);
	return (new);
}

// t_env_list	*ft_lstnew_two_values(void *key, void *content)
// {
// 	t_env_list	*new;

// 	new = (t_env_list *) malloc(sizeof(t_env_list));
// 	if (!new)
// 		return (NULL);
// 	new->key = key;
// 	new->content = content;
// 	new->next = (NULL);
// 	return (new);
// }
