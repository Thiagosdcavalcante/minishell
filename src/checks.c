/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 15:31:22 by tsantana          #+#    #+#             */
/*   Updated: 2024/07/09 15:56:04 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec(t_mini *data, t_root *root)
{
	pid_t	pid;
	int		status;

	if(root->left)
		ft_exec(data, root->left);
	pid = fork();
			// printf("achou\n");
	if (pid == 0)
	{
		char *teste = ft_strdup(root->word);
		ft_execute(data, teste);
		free(teste);
		// printf("achou:%s\n", root->word);
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0);
	if (root->right != NULL)
	{
		// printf("foi pra direita\n");
		ft_exec(data, root->right);
	}
	return (1);
}

int	init_exec(t_mini *data, t_root *root)
{
	return (ft_exec(data, root));
}

// void	check_commands(t_mini *data)
// {
// 	printf("teste");
// }
