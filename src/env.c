/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:28:08 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/08/14 14:46:08 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(t_mini *data, char **cmd)
{
	t_env_list	*temp;
	char		*teste;

	temp = data->envs;
	while (temp)
	{
		teste = ft_strchr(temp->content, '=');
		if(*++teste != '\0')
			ft_putendl_fd(temp->content, 1);
		temp = temp->next;
	}
}

void	get_envs(t_data *data)
{
	char	*env;
	char	**envp;

	envp = __environ;
	while(*envp)
	{
		env = ft_substr(*envp, 0, ft_strlen(*envp));
		ft_lstadd_back_env(&(data->envs), ft_lstnew_env(env));
		envp++;
	}
}
