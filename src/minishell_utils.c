/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:41:47 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/08 17:29:57 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cond_minishell(t_mini **mini, int cond)
{
	if (cond == 1)
	{
		ft_exit((*mini), NULL);
		ffree((*mini));
		exit((*mini)->status);
	}
	else if (cond == 2)
	{
        add_history((*mini)->in_ms);
        free((*mini)->in_ms);
	}
	else if (cond == 3)
	{
		free((*mini)->in_ms);
		return (EXIT_FAILURE);
	}
	return (0);
}

int	verify_if_is_only_one_sinal(t_mini *mini)
{
	t_tokens	*tmp;

	tmp = mini->cmmds;
	if (is_file(tmp->type) == TRUE && !tmp->next)
	{
		mini->status = 2;
		free(mini->in_ms);
		free_tokens(&mini->cmmds);
		return (printf("bash: syntax error near unexpected token `newline'\n"), 2);
	}
	return (0);
}

void	first_step(t_mini *mini)
{
	add_history(mini->in_ms);
	mini->in_ms = put_space_ms(mini->in_ms);
	mini->cmmds = parse_str(mini->in_ms);
}

int	return_exit(char *str, int i)
{
	int	ret;

	ret = 0;
	if (str && i == 1)
	{
		ret = ft_atoi(str);
		if (ret < 0 && ret > -256)
			return (printf("exit\n"), (256 + ret));
	}
	return (printf("exit\n"), ret % 256);
}
