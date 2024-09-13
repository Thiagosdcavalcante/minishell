/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_order.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:16:40 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/12 22:33:48 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens_f	*change_order(t_tokens_f *tkn)
{
	t_tokens_f	*head;

	if (tkn->type == WORD)
		return (tkn);
	head = tkn;
	while (tkn && tkn->next && tkn->type != WORD && tkn->type != PIPE)
		tkn = tkn->next;
	if (tkn->type == WORD)
	{
		if (tkn->next)
		{
			tkn->next->prev = tkn->prev;
			tkn->prev->next = tkn->next;
		}
		else
			tkn->prev->next = NULL;
		tkn->next = head;
		head->prev = tkn;
		tkn->prev = NULL;
	}
	return (tkn);
}

int	unlink_here_doc(t_root_f *root)
{
	if (root == NULL)
		return (0);
	if (root->type == DOUBLELESSER)
	{
		if (root->right && root->right->word)
		{
			if (unlink(root->right->word) == -1)
			{
				perror("Error unlinking file");
				return (-1);
			}
		}
	}
	if (root->left)
		unlink_here_doc(root->left);
	if (root->right)
		unlink_here_doc(root->right);
	return (0);
}

char	*path_name(void)
{
	char	*eof;
	char	*path;

	eof = ft_put_zero();
	path = ft_strjoin("/tmp/", eof);
	free(eof);
	return (path);
}
