/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erpiana <erpiana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:24:53 by tsantana          #+#    #+#             */
/*   Updated: 2024/07/09 17:18:27 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_mtx(t_tokens *mtx)
{
	while (mtx->next)
		mtx = mtx->next;
	while (mtx)
	{
		ft_printf("%p - %p || %s - TOKEN: %d\n", mtx, mtx->prev, mtx->str, mtx->type);
		mtx = mtx->prev;
	}
}

static void	clear_exit(t_mini *mini)
{
	rl_clear_history();
	final_free(mini);
	free_envs(mini->envars);
	exit(EXIT_SUCCESS);
}

static void	if_exit(t_mini *mini)
{
	char	**matrix;
	int		j;

	j = -1;
	while (ft_isspace(mini->in_ms[j]))
		++j;
	if (ft_memcmp(&mini->in_ms[j], "exit", 4) == 0)
	{
		matrix = ft_split(&(mini->in_ms[j]), ' ');
		j = -1;
		if (ft_strlen(matrix[0]) == 4)
		{
			while (matrix[j] != NULL)
				++j;
			if (j <= 2)
			{
				free_split(matrix);
				clear_exit(mini);
			}
			printf("exit: too many arguments\n");
		}
		free_split(matrix);
	}
}

static void	add_item(t_mini *mini)
{
	add_history(mini->in_ms);
	mini->in_ms = put_space_ms(mini->in_ms);
	mini->cmmds = parse_str(mini->in_ms);
	print_mtx(mini->cmmds);
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

static int	check_quotes_and_double_quotes(char *str)
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
			{
				i++;
			}
			if (str[i] == '\0')
			{
				printf("Syntax error: quoted unclosed\n");
				return (FALSE);
			}
		}
		i++;
	}
	return (TRUE);
}

static void	minishell(t_mini *mini)
{
	int	status;

	status = 0;
	mini->in_ms = readline("minishell>$ ");
	if (!mini->in_ms)
		clear_exit(mini);
	if (check_if_only_spaces(mini) == TRUE)
	{
		add_history(mini->in_ms);
		free(mini->in_ms);
		return ;
	}
	if (check_quotes_and_double_quotes(mini->in_ms) == FALSE)
		return ;
	if_exit(mini);
	if (mini->in_ms[0] != '\0')
	{
		add_item(mini);
		mini->tree = create_tree(mini->cmmds);
		status = init_exec(mini, mini->tree);
	}
	final_free(mini);
}

int	main(void)
{
	t_mini	mini;

	mini = (t_mini){0};
	mini.envars = get_envs(__environ);
	get_paths(&mini, mini.envars);
	while (1)
		minishell(&mini);
	return (0);
}
