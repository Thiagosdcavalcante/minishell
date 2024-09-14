/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 23:16:25 by codespace         #+#    #+#             */
/*   Updated: 2024/09/14 18:33:52 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
