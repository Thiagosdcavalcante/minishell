/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:01:01 by tsantana          #+#    #+#             */
/*   Updated: 2024/08/18 19:59:55 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sig_heredoc(int sig_heredoc)
{
	static int	hered;

	if (sig_heredoc != -1)
		hered = sig_heredoc;
	return (hered);
}

void	sigint_handler(int sig_num)
{
	g_sig = sig_num;
	if (sig_heredoc(-1))
	{
		ft_printf("\n");
		close (STDIN_FILENO);
	}
	else
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig = 0;
	}
}

void	sig_handler(int sig_num)
{
	g_sig = sig_num;
}

void	init_sig(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
