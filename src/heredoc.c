/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 21:24:05 by tsantana          #+#    #+#             */
/*   Updated: 2024/08/18 19:49:33 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unlink_here_doc(t_root_f *operator)
{
	if (operator == NULL)
		return (0);
	if (operator->type == DOUBLELESSER)
	{
		if (unlink(operator->right->word) == -1)
		{
			perror("Error unlinking file");
			return (-1);
		}
	}
	if (operator->left)
		unlink_here_doc(operator->left);
	if (operator->right)
		unlink_here_doc(operator->right);
	return (0);
}

static char	*path_name(void)
{
	char	*eof;
	char	*path;

	eof = ft_put_zero();
	path = ft_strjoin("/tmp/", eof);
	free(eof);
	return (path);
}

static void heredoc_util(t_mini *data, char *line, int file)
{
	char *new_line = full_expansion(data, line);
	ft_putendl_fd(new_line, file);
	free(line);
	free(new_line);
}

static char	*ft_heredoc(t_mini *data, t_tokens_f *tokens)
{
	t_tokens_f	*cur;
	int			file;
	char		*line;
	char		*path;

	cur = tokens;
	path = path_name();
	file = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	while (1 && sig != 3)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strlen(line) == ft_strlen(cur->next->str)
		&& ft_strncmp(line, cur->next->str, ft_strlen(cur->next->str)) == 0)
		{
			free(line);
			break; ;
		}
		heredoc_util(data, line, file);
	}
	close(file);
	return (path);
}

void	ft_check_heredoc(t_mini *data, t_tokens_f *tokens)
{
	t_tokens_f *current;

	current = tokens;
	while (current)
	{
		if (current->type == DOUBLELESSER)
		{
			current->next->str = ft_heredoc(data, current);
		}
		current = current->next;
	}
	return ;
}
