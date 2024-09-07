/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:42:37 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/09/06 18:49:28 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_builtins(t_mini *data, t_root_f *root)
{
	int	ret;

	ret = 0;
	if (ft_strncmp(root->new_args[0], "env", 4) == 0)
		ret = ft_env(data, root->new_args);
	else if (ft_strncmp(root->new_args[0], "export", 7) == 0)
		ret = ft_export(data, root->new_args);
	else if (ft_strncmp(root->new_args[0], "unset", 6) == 0)
		ft_unset(data, root->new_args);
	else if (ft_strncmp(root->new_args[0], "echo", 5) == 0)
		ret = ft_echo(data, root->new_args);
	else if (ft_strncmp(root->new_args[0], "cd", 3) == 0)
		ret = ft_cd(data, root->new_args);
	else if (ft_strncmp(root->new_args[0], "pwd", 4) == 0)
		ft_pwd(data, root->new_args);
	else if (ft_strncmp(root->new_args[0], "exit", 5) == 0)
		ret = ft_exit(data, root->new_args);
	data->status = ret;
	return (ret);
}

static int	is_builtins(t_mini *data, t_root_f *root)
{
	(void)data;
	if (ft_strncmp(root->word, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(root->word, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(root->word, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(root->word, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(root->word, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(root->word, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(root->word, "exit", 5) == 0)
		return (1);
	else
		return (0);
}

void free_dup(t_mini *data)
{
	free_tokens(&data->cmmds);
	free_tree(data->tree);
	ffree(data);
	if (data->in_ms)
		free(data->in_ms);
	close (STDOUT_FILENO);
	close (STDIN_FILENO);
}

static void	ft_pipe(t_mini *data, t_root_f *root, int *fd, int is_left)
{
	int	status;

	status = 0;
	// set_sig_func(); pra q seria isso? está quebrando um teste de pipe
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

	set_sig_func(); //coloquei aqui e foi, é isso? lugar errado?
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

int	count_args(char **args)
{
	int count;

	if(!args)
		return (0);
	count = 0;
	while (args[count])
		count++;
	return (count);
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
			ft_execute(data, root->new_args);
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
