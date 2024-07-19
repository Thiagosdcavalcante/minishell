/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:42:37 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/07/13 14:32:13 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_pipe(t_data *data, t_root *root, int *fd, int is_left)
{
	if (is_left == 1)
	{
		dup2 (fd[1], STDOUT_FILENO);
		close (fd[0]);
		close (fd[1]);
		ft_exec (data, root->left);
	}
	else
	{
		dup2 (fd[0], STDIN_FILENO);
		close (fd[0]);
		close (fd[1]);
		ft_exec (data, root->right);
	}
}

void	ft_pipex(t_data *data, t_root *root)
{
	pid_t	pid[2];
	int		fd[2];
	int		status;

	if (pipe(fd) < 0)
		exit (0);
	pid[0] = fork();
	if (pid[0] == 0)
	{
		ft_pipe(data, root, fd, 1);
		exit(EXIT_SUCCESS);
	}
	pid[1] = fork();
	if (pid[1] == 0)
	{
		ft_pipe(data, root, fd, 0);
		exit(EXIT_SUCCESS);
	}
	close (fd[0]);
	close (fd[1]);
	waitpid (pid[0], &status, 0);
	waitpid (pid[1], &status, 0);
}

int	ft_exec(t_data *data, t_root *root)
{
	pid_t	pid;
	int		status;
	char	*teste;
	// int		fd[2];

	if (root->type == 1)
		ft_pipex(data, root);
	else if (root->type > 1)
		ft_init_redirect(data, root);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			teste = ft_strdup(root->word);
			ft_execute(data, teste);
			free(teste);
			// printf("achou\n");
			// printf("achou:%s\n", root->word);
			exit(EXIT_FAILURE);
		}
		else
			waitpid(pid, &status, 0);
	}
	return (1);
}

int	init_exec(t_data *data, t_root *root)
{
	return (ft_exec(data, root));
}
