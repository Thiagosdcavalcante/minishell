/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:58:43 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/07/16 21:30:44 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_heredoc(t_tokens *tokens)
{
	t_tokens	*current;
	char		*eof;
	int			file;
	char		*line;
	char		*path;

	current = tokens;
	eof = ft_strdup(current->next->word);
	//fazer nome dos arquivos ramdomicos
	path = ft_strjoin("/tmp/", ft_itoa(1));
	file = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strlen(line) == ft_strlen(eof)
		&& ft_strncmp(line, eof, ft_strlen(eof)) == 0)
		{
			free(line);
			break; ;
		}
		ft_putendl_fd(line, file);
		free(line);
	}
	close(file);
	return (eof);
}

void	ft_check_heredoc(t_tokens *tokens)
{
	t_tokens *current;

	current = tokens;
	while (current)
	{
		if (current->type == 5)
		{
			current->word = ft_heredoc(current);
		}
		current = current->next;
	}
	return ;
}
