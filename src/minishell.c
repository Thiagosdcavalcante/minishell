/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:56:12 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/14 13:33:03 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_sig;

static int	add_item(t_mini *mini)
{
	if (g_sig != 0)
	{
		final_free(mini);
		return (0);
	}
	process_reorganization(mini);
	mini->tokens = exec_tokens(mini->cmmds_order);
	mini->tree = create_tree(mini, mini->tokens);
	return (1);
}

int	check_if_only_spaces(char *str)
{
	int	flag;
	int	i;

	i = 0;
	flag = 0;
	while (str[i] != '\0')
	{
		if (ft_isspace(str[i]) == FALSE)
		{
			flag = 1;
			break ;
		}
		i++;
	}
	if (flag == 0)
		return (TRUE);
	return (FALSE);
}

static t_bool	check_quotes_and_double_quotes(char *str)
{
	int		i;
	char	finded_quote;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			finded_quote = str[i];
			i++;
			while (str[i] && str[i] != finded_quote)
				i++;
			if (str[i] == '\0')
				return (printf("Syntax error: quoted unclosed\n"), FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	tokens_checker(t_mini *mini)
{
	t_tokens	*check;

	if (is_file(mini->cmmds->type) == TRUE)
		if (verify_if_is_only_one_sinal(mini) != 0)
			return (1);
	check = mini->cmmds;
	while (check)
	{
		if (is_file(check->type) == TRUE && is_file(check->next->type) == TRUE)
		{
			cond_minishell(&mini, 4);
			return (1);
		}
		if ((is_file(check->type) == TRUE && check->next->type == PIPE)
			|| (check->type == PIPE && !check->next))
		{
			cond_minishell(&mini, 4);
			return (1);
		}
		check = check->next;
	}
	return (0);
}
static int	minishell(t_mini *mini)
{
	mini->in_ms = readline("minishell>$ ");
	if (!mini->in_ms)
		cond_minishell(&mini, 1);
	if (check_if_only_spaces(mini->in_ms) == TRUE)
		return (cond_minishell(&mini, 2));
	if (!check_quotes_and_double_quotes(mini->in_ms))
		return (cond_minishell(&mini, 3));
	if (mini->in_ms[0] != '\0')
	{
		first_step(mini);
		if (tokens_checker(mini) == 1)
				return (mini->status);
		// if (is_file(mini->cmmds->type) == TRUE) // colocar em loop
		// 	if (verify_if_is_only_one_sinal(mini) != 0)
		// 		return (mini->status);
		if (add_item(mini) == 0)
			return (130);
		mini->status = init_exec(mini, mini->tree);
		if (mini->tree != NULL)
			unlink_here_doc(mini->tree);
		final_free(mini);
	}
	if (term_signal(mini->status) == SIGQUIT)
		ft_putendl_fd("QUIT (core dumped)", STDERR_FILENO);
	return (mini->status);
}

int	main(void)
{
	t_mini		mini;
	t_termios	term;
	static int	ret;
	const int	backup_fd = dup(STDIN_FILENO);

	ret = 0;
	mini = (t_mini){0};
	get_envs(&mini);
	tcgetattr(STDIN_FILENO, &term);
	while (1)
	{
		init_sig();
		dup2(backup_fd, STDIN_FILENO);
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		ret = minishell(&mini);
		if (mini.exit == 1)
		{
			rl_clear_history();
			close_fds((int)backup_fd);
			ffree(&mini);
			exit(ret);
		}
	}
	close_fds((int)backup_fd);
	return (ret);
}
