/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:32:04 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/08/14 20:02:47 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ao começar a tokenizar pode se criar já o infile do heredoc
#include "minishell.h"

static void	change_fd(int fd, int change_fd)
{
	dup2(fd, change_fd);

	close(fd);
}

void	ft_redirect(t_mini *data, t_root_f *root)
{
	if (root->left->type > 1)
		ft_redirect(data, root->left);
	if (root->type == 2)
	{
		root->fd = open(root->right->word, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		change_fd(root->fd, STDOUT_FILENO);
		close(root->fd);
	}
	else if (root->type == 3 || root->type == 5)
	{
		root->fd = open(root->right->word, O_RDONLY, 0);
		change_fd(root->fd, STDIN_FILENO);
		close(root->fd);
	}
	else if (root->type == 4)
	{
		root->fd = open(root->right->word, O_WRONLY | O_CREAT | O_APPEND, 0666);
		change_fd(root->fd, STDOUT_FILENO);
		close(root->fd);
	}
	return ;
}

void	ft_init_redirect(t_mini *data, t_root_f *root)
{
	int	temp_std[2];

	temp_std[0] = dup(STDIN_FILENO);
	temp_std[1] = dup(STDOUT_FILENO);
	if(root->fd < 0)
		ft_redirect(data, root);
	ft_exec(data, root->left);
	dup2(temp_std[0], STDIN_FILENO);
	dup2(temp_std[1], STDOUT_FILENO);
	close(temp_std[0]);
	close(temp_std[1]);
}
