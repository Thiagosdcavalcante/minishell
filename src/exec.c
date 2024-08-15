/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:42:37 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/08/14 21:07:48 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_root para t_root_f
static void	ft_pipe(t_mini *data, t_root_f *root, int *fd, int is_left)
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

void	ft_pipex(t_mini *data, t_root_f *root)
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

static int	is_builtins(t_mini *data, t_root_f *root)
{
	(void)data;
	if (ft_strncmp(root->args[0], "env", 4) == 0)
		return (1);
	else if (ft_strncmp(root->args[0], "export", 7) == 0)
		return (1);
	else if (ft_strncmp(root->args[0], "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(root->args[0], "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(root->args[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(root->args[0], "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(root->args[0], "exit", 5) == 0)
		return (1);
	else
		return (0);
}

static void	exec_builtins(t_mini *data, t_root_f *root)
{
	if (ft_strncmp(root->args[0], "env", 4) == 0)
		ft_env(data, root->args);
	else if (ft_strncmp(root->args[0], "export", 7) == 0)
		ft_export(data, root->args);
	else if (ft_strncmp(root->args[0], "unset", 6) == 0)
		ft_unset(data, root->args);
	else if (ft_strncmp(root->args[0], "echo", 5) == 0)
		ft_echo(data, root->args);
	else if (ft_strncmp(root->args[0], "cd", 3) == 0)
		ft_cd(data, root->args);
	else if (ft_strncmp(root->args[0], "pwd", 4) == 0)
		ft_pwd(data, root->args);
	else if (ft_strncmp(root->args[0], "exit", 5) == 0)
		ft_exit(data, root->args);
}

int	ft_exec(t_mini *data, t_root_f *root)
{
	pid_t	pid;
	int		status;
	/* char	*teste; */

	if (root->type == 1)
		ft_pipex(data, root);
	else if (root->type > 1)
		ft_init_redirect(data, root);
	else if (is_builtins(data, root))
		exec_builtins(data, root);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			ft_execute(data, root->args);
			exit(EXIT_FAILURE);
		}
		else
			waitpid(pid, &status, 0);
	}
	return (1);
}

int	init_exec(t_mini *data, t_root_f *root)
{
	return (ft_exec(data, root));
}
