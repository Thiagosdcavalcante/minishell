/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 21:24:05 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/13 13:07:16 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_util(t_mini *data, char *line, int file)
{
	char	*new_line;

	new_line = full_expansion(data, line);
	ft_putendl_fd(new_line, file);
	free(line);
	free(new_line);
}

int	sig_heredoc(int sig_heredoc)
{
	static int	hered;

	if (sig_heredoc != -1)
		hered = sig_heredoc;
	return (hered);
}

char	*open_heredoc_file(char **eof, char *str)
{
	char	*path;

	path = path_name();
	*eof = ft_quotes(str);
	return (path);
}

int	heredoc_loop(t_mini *data, char *eof, int file)
{
	char	*line;
	int		i;

	i = 0;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			if (g_sig != SIGINT)
			{
				ft_printf("warning: here-document at line %d ", i);
				ft_printf("delimited by end-of-file (wanted `%s')\n", eof);
			}
			break ;
		}
		if (ft_strlen(line) == ft_strlen(eof)
			&& ft_strncmp(line, eof, ft_strlen(eof)) == 0)
		{
			free(line);
			break ;
		}
		heredoc_util(data, line, file);
		i++;
	}
	return (g_sig);
}

char	*str_heredoc(char *str, t_mini *data)
{
	int		file;
	char	*path;
	char	*eof;

	path = open_heredoc_file(&eof, str);
	file = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	signal(SIGINT, sig_hand_here);
	if (heredoc_loop(data, eof, file) == SIGINT)
	{
		free(path);
		close(file);
		return (free(eof), NULL);
	}
	close(file);
	return (free(eof), path);
}
