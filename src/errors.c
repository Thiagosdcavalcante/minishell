/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 23:16:25 by codespace         #+#    #+#             */
/*   Updated: 2024/09/12 21:25:01 by ajuliao-         ###   ########.fr       */
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
	exit(status);
}

void	free_dup(t_mini *data)
{
	free_tokens(&data->cmmds);
	free_tree(&data->tree);
	ffree(data);
	if (data->in_ms)
		free(data->in_ms);
	close (STDOUT_FILENO);
	close (STDIN_FILENO);
}
