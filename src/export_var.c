/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:05:06 by tsantana          #+#    #+#             */
/*   Updated: 2024/06/26 10:16:57 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

static int	is_equal(char a, char b)
{
	if (a == b)
		return (TRUE);
	return (FALSE);
}

static int	is_export(char *str)
{
	int	i;

	i = 0;
	while (str[i] && EXPORT[i])
	{
		if (is_equal(str[i], EXPORT[i]) == TRUE)
			break ;
		i++;
	}
	if ((i - 1) == 6)
		return (TRUE);
	return (FALSE);
}

int	custom_export(char *str, t_envs *envs)
{
	int	i;

	i = 0;
	if (is_export(str) == TRUE)
	{
		while (is_equal(str[i], EXPORT[i]) == TRUE)
			i++;
		while (ft_isspace(str[i++]))
		while (envs->next)
			envs = envs->next;
		if (!envs->next)
			envs->next = make_env_nodes(&str[i]);
		return (TRUE);
	}
	else
		return (FALSE);
}
