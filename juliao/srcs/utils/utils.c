/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandrejuliao <alexandrejuliao@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 11:10:50 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/07/07 11:31:50 by alexandreju      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_update_var(t_data *data,char *key, char *value)
{
	t_env_list	*data_temp;
	char	*temp;
	char	*full_temp;

	data_temp = data->envs;
	while(data_temp)
	{
		if (ft_strncmp(data_temp->content, key, ft_strlen(key)) == 0)
		{
			free(data_temp->content);
			temp = ft_strjoin(key,"=");
			full_temp = ft_strjoin(temp, value);
			free(temp);
			data_temp->content = full_temp;
		}
		data_temp = data_temp->next;
	}
}

t_bool	ft_search_var(t_data *data, char *key)
{
	t_env_list	*temp;

	temp = data->envs;
	while(temp)
	{
		if (ft_strncmp(temp->content, key, ft_strlen(key)) == 0)
			return (TRUE);
		temp = temp->next;
	}
	return (FALSE);
}

void	get_envs(t_data *data, char **envp)
{
	char	*env;

	get_paths(data, envp);
	while(*envp)
	{
		env = ft_substr(*envp, 0, ft_strlen(*envp));
		ft_lstadd_back_env(&(data->envs), ft_lstnew_env(env));
		envp++;
	}
}

void	get_paths(t_data *data, char **envp)
{
	int		i;
	char	*temp;

	i = 0;
	while (ft_strncmp(*envp, "PATH", 3))
		envp++;
	data->paths = ft_split(*envp, ':');
	temp = data->paths[0];
	data->paths[0] = ft_substr(temp, 5, ft_strlen(temp));
	free(temp);
	while (data->paths[i] != NULL)
	{
		temp = data->paths[i];
		data->paths[i] = ft_strjoin(temp, "/");
		free(temp);
		i++;
	}
}

void	ffree(t_data *data)
{
	int	i;
	t_env_list *temp;

	if (data->paths)
	{
		i = 0;
		while (data->paths[i])
		{
			free(data->paths[i]);
			i++;
		}
		free(data->paths);
	}
	if (data->envs)
	{
		while (data->envs)
		{
			temp = data->envs->next;
			free(data->envs->content);
			free(data->envs);
			data->envs = temp;
		}
	}
}

void	parray(char **arr)
{
	int i;

	i = 0;
	while(arr[i])
		printf("--:%s\n",arr[i++]);
}

void	plist(t_data *data, int c)
{
	if(c == 'c')
	{
		t_commands	*current;
		current = data->parser->commands;
		// printf("words:%s\n", data->parser->commands->word);
		while (current)
		{
			// printf("words:%s\n", current->word);
			current = current->next;
		}
	}

	if(c == 'e')
	{
		t_env_list	*current;
		current = data->envs;
		while (current)
		{
			printf("envs:%s\n",current->content);
			current = current->next;
		}
	}
	if (c == 'p')
	{
		t_parser *current_parser = data->parser;

		while (current_parser)
		{
			t_commands *current_command = current_parser->commands;

			while (current_command)
			{
				printf("word: %s\n", current_command->word);
				current_command = current_command->next;
			}

			printf("type: %d\n", current_parser->type);
			current_parser = current_parser->next;
		}
    }
	if (c == 't')
	{

		t_tokens	*current;
		current = data->tokens;
		// current = ft_lstlast_token(data->tokens);
		while (current)
		{
			printf("words:%s\n", current->word);
			printf("type:%d\n", current->type);
			current = current->next;
		}
	}
	return ;
}
void	ptokens(t_tokens *tokens, int c)
{
	printf("words:\n");
	if (c == 't')
	{

		t_tokens	*current;
		current = tokens;
		// current = ft_lstlast_token(data->tokens);
		while (current)
		{
			printf("words:%s\n", current->word);
			printf("type:%d\n", current->type);
			current = current->next;
		}
	}
	return ;
}
