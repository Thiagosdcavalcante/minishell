/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:42:37 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/09/10 16:57:52 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_pipe(t_mini *data, t_root_f *root, int *fd, int is_left)
{
	int	status;

	status = 0;
	if (is_left == 1)
	{
		dup2(fd[1], STDOUT_FILENO);
		close (fd[0]);
		close (fd[1]);
		rl_clear_history();
		status = ft_exec(data, root->left);
		free_dup(data);
		exit (status);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close (fd[0]);
		close (fd[1]);
		status = ft_exec(data, root->right);
		free_dup(data);
		exit (status);
	}
}

void	ft_pipex(t_mini *data, t_root_f *root)
{
	pid_t	pid[2];
	int		fd[2];
	int		status;

	set_sig_func();
	status = 0;
	if (pipe(fd) < 0)
		exit(EXIT_FAILURE);
	pid[0] = fork();
	if (pid[0] == 0)
		ft_pipe(data, root, fd, 1);
	pid[1] = fork();
	if (pid[1] == 0)
		ft_pipe(data, root, fd, 0);
	close(fd[0]);
	close(fd[1]);
	status = ft_status(pid[0]);
	status = ft_status(pid[1]);
	data->status = status;
}

int	ft_exec(t_mini *data, t_root_f *root)
{
	pid_t	pid;

	if (root->type == PIPE)
		ft_pipex(data, root);
	else if (root->left != NULL && root->type > PIPE)
		ft_init_redirect(data, root);
	else if (is_builtins(data, root))
		exec_builtins(data, root);
	else if (root->new_args)
	{
		pid = fork();
		if (pid == 0)
		{
			set_sig_func();
			ft_execute(data, root->new_args);
			free_tree(&data->tree);
			exit(0);
		}
		else
			sig_exec();
		data->status = ft_status(pid);
	}
	return (data->status);
}

int	init_exec(t_mini *data, t_root_f *root)
{
	return (ft_exec(data, root));
}
