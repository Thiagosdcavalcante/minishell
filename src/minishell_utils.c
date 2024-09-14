/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:41:47 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/14 18:33:23 by tsantana         ###   ########.fr       */
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
		if ((*mini)->in_ms[0] != '\0')
			add_history((*mini)->in_ms);
		free((*mini)->in_ms);
	}
	else if (cond == 3)
	{
		free((*mini)->in_ms);
		return (EXIT_FAILURE);
	}
	else if (cond == 4)
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		final_free((*mini));
		return (1);
	}
	return (0);
}

int	verify_if_is_only_one_sinal(t_mini *mini)
{
	t_tokens	*tmp;

	tmp = mini->cmmds;
	if ((is_file(tmp->type) == TRUE && !tmp->next) || tmp->next->type > 1)
	{
		mini->status = 2;
		free(mini->in_ms);
		free_tokens(&mini->cmmds);
		free_tokens(&mini->cmmds_order);
		printf("bash: syntax error near unexpected token `newline'\n");
		return (2);
	}
	return (0);
}

void	first_step(t_mini *mini)
{
	if (mini->in_ms[0] != '\0')
		add_history(mini->in_ms);
	mini->in_ms = put_space_ms(mini->in_ms);
	mini->cmmds = parse_str(mini->in_ms, mini);
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

void	my_error(t_mini *data, int status, char *msg, char *command)
{
	if (status == EACCES)
		status = 126;
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	if (data)
		final_free(data);
	ffree(data);
	exit(status);
}
