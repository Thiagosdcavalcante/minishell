/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:56:12 by tsantana          #+#    #+#             */
/*   Updated: 2024/08/18 19:58:14 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_sig = 0;

/* static void	clear_exit(t_mini *mini) */
/* { */
/* 	rl_clear_history(); */
/* 	final_free(mini); */
/* 	free_envs(mini->envs); */ 
/* 	exit(EXIT_SUCCESS); */
/* } */
/**/
/* static void	if_exit(t_mini *mini) */
/* { */
/* 	char	**matrix; */
/* 	int		j; */
/**/
/* 	j = -1; */
/* 	if (ft_memcmp(&mini->in_ms[j], "exit", 4) == 0) */
/* 	{ */
/* 		matrix = ft_split(&(mini->in_ms[j]), ' '); */
/* 		j = -1; */
/* 		if (ft_strlen(matrix[0]) == 4) */
/* 		{ */
/* 			while (matrix[j] != NULL) */
/* 				++j; */
/* 			if (j <= 2) */
/* 			{ */
/* 				free_split(matrix); */
/* 				clear_exit(mini); */
/* 			} */
/* 			printf("exit: too many arguments\n"); */
/* 		} */
/* 		free_split(matrix); */
/* 	} */
/* } */

// static void print_tree(t_root_f *root, int nivel) {
//     int i;
//     if (root) { 
//         print_tree(root->right, nivel + 1); 
//         printf("\n\n"); 
//         for (i = 0; i < nivel; i++) 
//             printf("\t"); 
//         printf("%s - %d\n", root->word ? root->word : "NULL", root->type); 
//         print_tree(root->left, nivel + 1); 
//     } 
// } 

static void	add_item(t_mini *mini)
{
	add_history(mini->in_ms);
	mini->in_ms = put_space_ms(mini->in_ms);
	mini->cmmds = parse_str(mini->in_ms);
	mini->tokens = exec_tokens(mini->cmmds);
	ft_check_heredoc(mini, mini->tokens);
	mini->tree = create_tree(mini->tokens);
	// print_tree(mini->tree, 1);
}

static t_bool	check_if_only_spaces(t_mini *mini)
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
	while (str[i++] != '\0')
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
	}
	return (TRUE);
}

static int	minishell(t_mini *mini)
{
	int	status;

	mini->in_ms = readline("minishell>$ ");
	if (!mini->in_ms)
		return (ft_exit(mini, NULL));
	if (check_if_only_spaces(mini) == TRUE)
	{
		add_history(mini->in_ms);
		if (mini->in_ms)
		{
			free(mini->in_ms);
			return (printf("exit: %s: numeric argument required", mini->paths[2]), 2);
		}
	}
	if (!check_quotes_and_double_quotes(mini->in_ms))
		return (EXIT_FAILURE);
	/* if_exit(mini); */
	if (mini->in_ms[0] != '\0')
		add_item(mini);
	status = init_exec(mini, mini->tree);
	// if (mini->tree != NULL)
	// 	unlink_here_doc(mini->tree);
	final_free(mini);
	return (0);
}

int	main(void)
{
	t_mini		mini;
	static int	ret;

	ret = 0;
	init_sig();
	mini = (t_mini){0};
	get_envs(&mini);
	while (1 && sig < 3 )
		ret = ((minishell(&mini)) % 256);
	return (ret);
}
