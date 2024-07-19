/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:47:59 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/03/16 10:38:13 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	insert_end(t_char **root, char value)
{
	t_char	*new_t_char;
	t_char	*curr;

	new_t_char = malloc(sizeof(t_char));
	if (new_t_char == NULL)
		return ;
	new_t_char->content = value;
	new_t_char->next = NULL;
	if (*root == NULL)
	{
		*root = new_t_char;
		return ;
	}
	curr = *root;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new_t_char;
}

size_t	find_n(t_char **list)
{
	t_char	*curr;

	curr = *list;
	while (curr)
	{
		if (curr->content == '\n')
			return (1);
		curr = curr->next;
	}
	return (0);
}

void	copy_txt(t_char **list, char *str)
{
	int		i;
	t_char	*temp;

	i = 0;
	while (*list && (*list)->content != '\n')
	{
		str[i++] = (*list)->content;
		temp = *list;
		*list = (*list)->next;
		free(temp);
	}
	if (*list && (*list)->content == '\n')
	{
		str[i++] = (*list)->content;
		temp = *list;
		*list = (*list)->next;
		free(temp);
	}
	str[i] = '\0';
}

size_t	str_len(t_char **list)
{
	size_t	len;
	t_char	*curr;

	if (!list || !*list)
		return (0);
	len = 0;
	curr = *list;
	while (curr && curr->content != '\n' )
	{
		curr = curr->next;
		len++;
	}
	return (++len);
}
