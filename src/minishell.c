/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:56:12 by tsantana          #+#    #+#             */
/*   Updated: 2024/08/26 21:40:09 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_sig = 0;

void print_list(t_tokens *cmd)
{
	while(cmd)
	{
		printf("TOKEN: %s", cmd->str);
		cmd = cmd->next;
	}

}

static void	add_item(t_mini *mini)
{
	add_history(mini->in_ms);
	mini->in_ms = put_space_ms(mini->in_ms);
	mini->cmmds = parse_str(mini->in_ms);
	mini->tokens = exec_tokens(mini->cmmds);
	mini->tree = create_tree(mini->tokens);
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
		return (ft_exit(mini, NULL));
	// if (check_if_only_spaces(mini) == TRUE)
	// {
	// 	add_history(mini->in_ms);
	// 	free(mini->in_ms);
	// 	return (printf("exit: %s: numeric argument required", mini->paths[2]), 2);
	// }
	if (!check_quotes_and_double_quotes(mini->in_ms))
		return (EXIT_FAILURE);
	if (mini->in_ms[0] != '\0')
	{

		add_item(mini);
		status = init_exec(mini, mini->tree);
		mini->status = status;
		if (mini->tree != NULL)
			unlink_here_doc(mini->tree);
		all_free(mini);
	}
	return (mini->status);
}

int	main(void)
{
	t_mini		mini;
	static int	ret;

	ret = 0;
	init_sig();
	mini = (t_mini){0};
	get_envs(&mini);
	while (1)
	{
		ret = minishell(&mini);
		if (mini.exit == 1)
		{
			rl_clear_history();
			exit(ret);
		}
	}
	return (ret);
}
