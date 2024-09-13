/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:48:41 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/09/12 22:23:27 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtins(t_mini *data, t_root_f *root)
{
	int	ret;

	ret = 0;
	if (ft_strncmp(root->n_args[0], "env", 4) == 0)
		ret = ft_env(data, root->n_args);
	else if (ft_strncmp(root->n_args[0], "export", 7) == 0)
		ret = ft_export(data, root->n_args);
	else if (ft_strncmp(root->n_args[0], "unset", 6) == 0)
		ret = ft_unset(data, root->n_args);
	else if (ft_strncmp(root->word, "echo", 4) == 0)
		ret = ft_echo(data, root);
	else if (ft_strncmp(root->n_args[0], "cd", 3) == 0)
		ret = ft_cd(data, root->n_args);
	else if (ft_strncmp(root->n_args[0], "pwd", 4) == 0)
		ft_pwd(data, root->n_args);
	else if (ft_strncmp(root->n_args[0], "exit", 5) == 0)
		ret = ft_exit(data, root->n_args);
	data->status = ret;
	return (ret);
}

int	is_builtins(t_mini *data, t_root_f *root)
{
	(void)data;
	if (ft_strncmp(root->word, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(root->word, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(root->word, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(root->word, "echo", 4) == 0)
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

char	*ft_quotes(char *word)
{
	char	*file;
	int		i;
	int		j;

	if (!word)
		return (NULL);
	file = (char *)malloc(ft_strlen(word) + 1);
	if (!file)
		return (NULL);
	i = 0;
	j = 0;
	while (word[i])
	{
		if (word[i] != '"' && word[i] != '\'')
		{
			file[j] = word[i];
			j++;
		}
		i++;
	}
	file[j] = '\0';
	return (file);
}

t_tokens_f	*ft_lstlast_token_f(t_tokens_f *tokens)
{
	if (!tokens)
		return (NULL);
	while (tokens && tokens->next)
	{
		tokens = tokens->next;
	}
	return (tokens);
}
