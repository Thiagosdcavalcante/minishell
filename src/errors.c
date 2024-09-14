/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 23:16:25 by codespace         #+#    #+#             */
/*   Updated: 2024/09/14 12:42:21 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_error(t_mini *data, int status, char *msg, char *command)
{
	(void)data;
	if (status == EACCES)
		status = 126;
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	if(data)
		final_free(data);
	ffree(data);
	exit(status);
}

void	free_dup(t_mini *data)
{
	free_tokens(&data->cmmds);
	free_tokens(&data->cmmds_order);
	free_tree(&data->tree);
	ffree(data);
	if (data->in_ms)
		free(data->in_ms);
	close (STDOUT_FILENO);
	close (STDIN_FILENO);
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

void	ft_strcpy(char *dst, const char *src)
{
	if (src && dst)
	{
		while (*src)
			*dst++ = *src++;
		*dst = '\0';
	}
}

void	print_eof(int i, char *eof)
{
	ft_printf("warning: here-document at line %d ", i);
	ft_printf("delimited by end-of-file (wanted `%s')\n", eof);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

