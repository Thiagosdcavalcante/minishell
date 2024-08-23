/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:32:04 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/08/23 16:22:39 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strip_quotes(char *word)
{
	char	*file;

	if ((word[0] == '"' && word[ft_strlen(word) - 1] == '"') ||
		(word[0] == '\'' && word[ft_strlen(word) - 1] == '\''))
	{
		file = ft_substr(word, 1, ft_strlen(word) - 2);
	}
	else
		file = word;
	return (file);
}

int	ft_redirect_lesser(t_root_f *root)
{
    char *file;

	file = ft_strip_quotes(root->right->word);
    if ((root->fd = open(file, O_RDONLY)) == -1)
	{
        perror("minishell: open error");
        free(file);
        return -1;
    }
    dup2(root->fd, STDIN_FILENO);
    close(root->fd);
    free(file);
    return 0;
}

int	ft_redirect_greater(t_root_f *root)
{
    char *file;

	file = ft_strip_quotes(root->right->word);
    if ((root->fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
	{
        perror("minishell: open error"); 
        free(file);
        return -1;
    }
    if (dup2(root->fd, STDOUT_FILENO) == -1)
	{
        perror("minishell: dup2 error");
        close(root->fd);
        free(file);
        return -1;
    }
    close(root->fd);
    free(file);
    return 0;
}

int	ft_redirect_doublegreater(t_root_f *root)
{
    char *file;

	file = ft_strip_quotes(root->right->word);
    if ((root->fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666)) == -1)
	{
        perror("minishell: open error");
        free(file);
        return -1;
    }

    if (dup2(root->fd, STDOUT_FILENO) == -1)
	{
        perror("minishell: dup2 error");
        close(root->fd);
        free(file);
        return -1;
    }

    close(root->fd);
    free(file);
    return 0;
}

int	ft_redirect(t_mini *data, t_root_f *root)
{
	int	result = 0;

	if (root->left && root->left->type > PIPE)
	{
		result = ft_redirect(data, root->left);
		if (result == -1)
			return (-1);
	}
	if (root->type == GREATER)
		result = ft_redirect_greater(root);
	else if (root->type == LESSER || root->type == DOUBLELESSER)
		result = ft_redirect_lesser(root);
	else if (root->type == DOUBLEGREATER)
		result = ft_redirect_doublegreater(root);
	return (result);
}

void	ft_init_redirect(t_mini *data, t_root_f *root)
{
	int	temp_std[2];

	temp_std[0] = dup(STDIN_FILENO);
	temp_std[1] = dup(STDOUT_FILENO);
	if(root->fd < 0)
	{
		if (ft_redirect(data, root) == -1)
		{
			dup2(temp_std[0], STDIN_FILENO);
			dup2(temp_std[1], STDOUT_FILENO);
			close(temp_std[0]);
			close(temp_std[1]);
			data->status = 1;
			return ;
		}
	}
	ft_exec(data, root->left);
	dup2(temp_std[0], STDIN_FILENO);
	dup2(temp_std[1], STDOUT_FILENO);
	close(temp_std[0]);
	close(temp_std[1]);
}
