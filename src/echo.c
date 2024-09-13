/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:02:22 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/09/12 22:23:27 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_has_n(char **cmd)
{
	int	i;
	int	j;

	i = 1;
	if (cmd[i] == NULL)
		return (i);
	while (cmd[i] != NULL)
	{
		if (ft_strncmp(cmd[i], "-n", 2) == 0)
		{
			j = 2;
			while (cmd[i][j] != '\0' && cmd[i][j] == 'n')
				j++;
			if (cmd[i][j] != '\0')
				break ;
		}
		else
			break ;
		i++;
	}
	return (i);
}

static void	print_echo(char **cmd, int start)
{
	int	i;

	i = start;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
}

int	ft_echo(t_mini *data, t_root_f *root)
{
	int	i;

	(void)data;
	i = 0;
	if (root->word[4] != '\0')
	{
		printf("minishell: %s: command not found\n", root->word);
		return (1);
	}
	if (root->n_args[1] == NULL)
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	i = ft_has_n(root->n_args);
	print_echo(root->n_args, i);
	if (ft_has_n(root->n_args) == 1)
		ft_putchar_fd('\n', 1);
	return (0);
}

int	is_directory(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}
