/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:32:36 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/08/14 14:45:33 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd(t_mini *data, char **cmd)
{
	char	*pwd;

	if (ft_strncmp(cmd[0], "pwd", 4) == 0)
	{
		pwd = getcwd(NULL, 0);
		if (pwd == NULL)
		{
			perror("pwd");
			return ;
		}
		ft_putendl_fd(pwd, 1);
		free(pwd);
	}
	return ;
}
