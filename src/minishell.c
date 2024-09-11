/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:56:12 by tsantana          #+#    #+#             */
/*   Updated: 2024/09/11 17:32:01 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_sig;

void	print_tree(t_root_f *root, int nivel)
{
	int	i;

	if (root)
	{
		print_tree(root->right, nivel + 1);
		printf("\n\n");
		for(i = 0; i < nivel; i++)
			printf("\t");
		printf("%s - %d", root->word, root->type);
		print_tree(root->left, nivel + 1);
	}
}

void print_list_tokens(t_tokens_f *cmd)
{
	while (cmd)
	{
		if (cmd->str)
			printf("TOKEN: %s - TYPE: %d\n", cmd->str, cmd->type);
		else
			printf("TOKEN: (null) - TYPE: %d\n", cmd->type);

		cmd = cmd->next;
	}
}

static int	add_item(t_mini *mini)
{
	if (g_sig != 0)
		return (final_free(mini), 0);
	mini->tokens = exec_tokens(mini->cmmds);
	mini->tokens = change_order(mini->tokens);
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
