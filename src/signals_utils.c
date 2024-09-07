/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:38:36 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/06 16:33:48 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(int bckp_fd)
{
	close(bckp_fd);
	close(0);
	close(1);
	close(2);
}

void	sig_hand_here(int signal)
{
	(void)signal;
	ft_printf("\n");
	close(STDIN_FILENO);
	g_sig = SIGINT;
}

int	ft_status(pid_t pid)
{
	int	status;

	waitpid (pid, &status, 0);
	status = get_return_value(status);
	return (status);
}

void	set_sig_func(void)
{
	close(3);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}