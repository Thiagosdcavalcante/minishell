/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:56:12 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/13 16:17:37 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_sig;

void print_list(t_tokens *cmd)
{
	while(cmd)
	{
		printf("TOKEN: %s\n", cmd->str);
		cmd = cmd->next;
	}

}

static int	add_item(t_mini *mini)
{
	if (g_sig != 0)
		return (final_free(mini), 0);
	process_reorganization(mini);
	mini->tokens = exec_tokens(mini->cmmds_order);
	mini->tree = create_tree(mini, mini->tokens);
	return (1);
}

static int	check_if_only_spaces(t_mini *mini)
{
	int	flag;
	int	i;

	i = 0;
	flag = 0;
	while (mini->in_ms[i] != '\0')
	{
		if (ft_isspace(mini->in_ms[i]) == FALSE)
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
	if (str[0] == '|' || str[ft_strlen(str) - 1] == '|')
		return (printf("bash: syntax error near unexpected token `|'\n"), 0);
	if (str[ft_strlen(str) - 1] == '<' || str[ft_strlen(str) - 1] == '>')
		return (printf("bash: syntax error near unexpected token `newline'\n"), 0);
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

static int	minishell(t_mini *mini)
{
	int	status;

	status = 0;
	mini->in_ms = readline("minishell>$ ");
	if (!mini->in_ms)
		cond_minishell(&mini, 1);
	if (check_if_only_spaces(mini) == TRUE)
		return (cond_minishell(&mini, 2));
	if (!check_quotes_and_double_quotes(mini->in_ms))
		return (cond_minishell(&mini, 3));
	if (mini->in_ms[0] != '\0')
	{
		first_step(mini);
		if (is_file(mini->cmmds->type) == TRUE)
			if (verify_if_is_only_one_sinal(mini) != 0)
				return (mini->status);
		if (add_item(mini) == 0)
			return (130);
		status = init_exec(mini, mini->tree);
		mini->status = status;
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
