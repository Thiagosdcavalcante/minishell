/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:01:01 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/14 14:38:49 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile int	g_sig;

void	sig_handler(int sig_num)
{
	g_sig = sig_num;
	printf("\n");
}

void	sig_exec(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	sigint_handler(int sig_num)
{
	g_sig = sig_num;
	if (sig_heredoc(-1))
	{
		printf("\n");
		close (STDIN_FILENO);
	}
	else
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig = 0;
	}
}

void	sigint_handler_exec(int sig_num)
{
	g_sig = sig_num;
	rl_on_new_line();
	rl_replace_line("", 0);
	g_sig = 0;
}

void	init_sig(void)
{
	g_sig = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
