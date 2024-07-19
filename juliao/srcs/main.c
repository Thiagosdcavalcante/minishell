/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:16:25 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/07/15 19:07:31 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		printf("teste");
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*input;
	char	**command;
	int		status;

	(void)argc;
	(void)argv;
	if (env)
		data.exit = 0;
	// signal(SIGINT, handle_signal);
	data.envs = NULL;
	get_envs(&data, env);
	data.exit = 1;
	data.tokens = NULL;
	status = 1;
	while (status)
	{
		input = readline("->");
		if (!input)
		{
			break ;
		}
		if (strcmp(input, "exit") == 0)
		{
			free(input);
			ffree(&data);
			status = 0;
			break ;
		}
		add_history(input);
		init_read(&data, input);
		status = init_exec(&data, data.tree);
		free(input);
	}
	printf("Bye.\n");
	return (0);
}
