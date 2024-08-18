/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:01:01 by tsantana          #+#    #+#             */
/*   Updated: 2024/08/18 18:00:44 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig_num)
{
    signal(SIGINT, sigint_handler); 
	g_sig = 1;
}

void	sigquit_handler(int sig_num)
{
    signal(SIGQUIT, sigquit_handler);
	g_sig = 3;
}
