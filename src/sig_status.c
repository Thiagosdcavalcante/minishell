/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 20:36:24 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/03 20:40:17 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

static int    term_by_signal(int status)
{
    return (((signed char)((status & 0x7f) + 1) >> 1) > 0);
}

static int    term_normaly(int status)
{
    return (term_by_signal(status) == 0);
}

static int    exit_status(int status)
{
    return ((status >> 8) & 0xFF);
}

static int    term_signal(int status)
{
    return (status & 0x7F);
}

int    get_return_value(int status)
{
    if (term_by_signal(status))
    {
        if (term_signal(status) == SIGQUIT)
            ft_putendl_fd("QUIT (core dumped)", STDERR_FILENO);
        return (term_signal(status) + 128);
    }
    return (exit_status(status));
}
