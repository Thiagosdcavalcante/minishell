/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:36:24 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/13 16:44:44 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	term_by_signal(int status)
{
	return (((signed char)((status & 0x7f) + 1) >> 1) > 0);
}

// static int	term_normaly(int status)
// {
// 	return (term_by_signal(status) == 0);
// }

static int	exit_status(int status)
{
	return ((status >> 8) & 0xFF);
}

int	term_signal(int status)
{
	return (status & 0x7F);
}

int	get_return_value(int status)
{
	if (term_by_signal(status))
		return (term_signal(status) + 128);
	return (exit_status(status));
}
