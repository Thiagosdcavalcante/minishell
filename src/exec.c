/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:42:37 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/08/18 16:53:48 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd_fork(int *fd, char *error)
{
	if (error)
		perror(error);
	if (*fd)
	{
		close(fd[0]);
		if (fd[1])
			close(fd[1]);
	}
}

static void	ft_pipe(t_mini *data, t_root_f *root, int *fd, int is_left)
{
	int	status;

	status = 0;
	if (is_left == 1)
	{
		dup2(fd[1], STDOUT_FILENO);
		close (fd[0]);
		close (fd[1]);
		status = ft_exec (data, root->left);
		exit (status);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close (fd[0]);
		close (fd[1]);
		status = ft_exec (data, root->right);
		exit (status);
	}
}

static int	ft_status(pid_t pid)
{
	int	status;

	waitpid (pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}

void	ft_pipex(t_mini *data, t_root_f *root)
{
	pid_t	pid[2];
	int		fd[2];
	int		status;

	status = 0;
	if (pipe(fd) < 0)
		exit (0);
	pid[0] = fork();
	if (pid[0] == 0)
	{
		ft_pipe(data, root, fd, 1);
	}
	pid[1] = fork();
	if (pid[1] == 0)
	{
		ft_pipe(data, root, fd, 0);
	}
	close (fd[0]);
	close (fd[1]);
	status = ft_status(pid[0]);
	status = ft_status(pid[1]);
	data->status = status;
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

static int	exec_builtins(t_mini *data, t_root_f *root)
{
	int	ret;

	ret = 0;
	// init_expansion(data, root->args);
	if (ft_strncmp(root->args[0], "env", 4) == 0)
		ret = ft_env(data, root->args);
	else if (ft_strncmp(root->args[0], "export", 7) == 0)
		ret = ft_export(data, root->args);
	else if (ft_strncmp(root->args[0], "unset", 6) == 0)
		ft_unset(data, root->args);
	else if (ft_strncmp(root->args[0], "echo", 5) == 0)
		ret = ft_echo(data, root->args);
	else if (ft_strncmp(root->args[0], "cd", 3) == 0)
		ret = ft_cd(data, root->args);
	else if (ft_strncmp(root->args[0], "pwd", 4) == 0)
		ft_pwd(data, root->args);
	else if (ft_strncmp(root->args[0], "exit", 5) == 0)
		ret = ft_exit(data, root->args);
	data->status = ret;
	return (ret);
}

int	ft_exec(t_mini *data, t_root_f *root)
{
	pid_t	pid;

	init_expansion(data, root->args);
	if (root->type == PIPE)
		ft_pipex(data, root);
	else if (root->type > PIPE)
		ft_init_redirect(data, root);
	else if (is_builtins(data, root))
		exec_builtins(data, root);
	else
	{
		pid = fork();
		if (pid == 0)
			ft_execute(data, root->args);
		data->status = ft_status(pid);
	}
	return (data->status);
}

int	init_exec(t_mini *data, t_root_f *root)
{
	return (ft_exec(data, root));
}
