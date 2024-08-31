/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:42:37 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/08/30 21:18:48 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_status(pid_t pid)
{
	int	status;

	waitpid (pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}

static int	exec_builtins(t_mini *data, t_root_f *root)
{
	int	ret;

	ret = 0;
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
		// free_tree(data->tree);
		exit (status);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close (fd[0]);
		close (fd[1]);
		status = ft_exec(data, root->right);
		exit (status);
	}
}

void ft_pipex(t_mini *data, t_root_f *root)
{
	pid_t	pid[2];
	int		fd[2];
	int		status;

	status = 0;
	if (pipe(fd) < 0)
		exit(EXIT_FAILURE);
	if ((pid[0] = fork()) == 0)
		ft_pipe(data, root, fd, 1);
	if ((pid[1] = fork()) == 0)
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

	// if (root->args != NULL)
	// 	init_expansion(data, root->args);
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
		{
			ft_execute(data, root->args);
			// free_tree(data->tree);
			exit(0);
		}
		data->status = ft_status(pid);
	}
	return (data->status);
}

int	init_exec(t_mini *data, t_root_f *root)
{
	return (ft_exec(data, root));
}
