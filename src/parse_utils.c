/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:56:02 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/11 14:48:51 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	search_type(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '|' && !str[i + 1])
		return (PIPE);
	else if (str[i] == '>' && !str[i + 1])
		return (GREATER);
	else if (str[i] == '<' && !str[i + 1])
		return (LESSER);
	else if (str[i] == '<' && str[i + 1] == '<')
		return (DOUBLELESSER);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (DOUBLEGREATER);
	else
		return (WORD);
}

static t_tokens	*define_word(t_tokens *lst)
{
	t_tokens	*temp;
	t_tokens	*head;

	head = lst;
	temp = lst;
	while (temp)
	{
		if (temp->prev && temp->type == WORD && is_file(temp->prev->type))
			temp->type = MS_FILE;
		temp = temp->next;
	}
	return (head);
}

static t_tokens	*create_mtx(char *str)
{
	t_tokens	*ms;

	ms = malloc(sizeof(t_tokens));
	if (!ms)
		return (NULL);
	ms->str = ft_strdup(str);
	ms->type = search_type(str);
	ms->next = NULL;
	ms->prev = NULL;
	return (ms);
}

static char	*str_heredoc(char *str, t_mini *data)
{
	int			file;
	char		*line;
	char		*path;
	char		*eof;

	path = path_name();
	file = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	eof = ft_quotes(str);
	signal(SIGINT, sig_hand_here);
	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL)
		{
			if (g_sig != SIGINT)
				ft_printf("warning: here-document at line 1 delimited by end-of-file (wanted `%s')\n", eof);
			break ;
		}
		if (ft_strlen(line) == ft_strlen(eof)
			&& ft_strncmp(line, eof, ft_strlen(eof)) == 0)
		{
			free(line);
			break ;
		}
		heredoc_util(data, line, file);
	}
	close(file);
	if (g_sig == SIGINT)
	{
		free(path);
		return (free(eof), NULL);
	}
	return (free(eof), path);
}

static t_tokens	*create_heredoc_file(char *str, t_mini *mini)
{
	t_tokens	*ms;

	ms = malloc(sizeof(t_tokens));
	if (!ms)
		return (NULL);
	ms->type = search_type(str);
	ms->str = str_heredoc(str, mini);
	ms->next = NULL;
	ms->prev = NULL;
	return (ms);
}

t_tokens	*parse_str(char *str, t_mini *mini)
{
	char		**parse_str;
	t_tokens	*mtx;
	t_tokens	*head;
	int			i;

	if (!str)
		return (NULL);
	i = 0;
	mtx = NULL;
	parse_str = custom_split(str, ' ');
	mtx = create_mtx(parse_str[i]);
	if (!mtx)
		return (NULL);
	head = mtx;
	while (parse_str[++i])
	{
		if (mtx && mtx->type == DOUBLELESSER)
			mtx->next = create_heredoc_file(parse_str[i], mini);
		else
			mtx->next = create_mtx(parse_str[i]);
		mtx->next->prev = mtx;
		mtx = mtx->next;
	}
	free_split(parse_str);
	return (define_word(head));
}
