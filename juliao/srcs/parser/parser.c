/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 01:19:50 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/07/16 21:31:26 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_put_zero(char	*number)
{
	char	*result;
	int		size;
	char	*final;

	result = NULL;
	size = ft_strlen(number);
	result = ft_strjoin("0", number);
	if( size < 4)
		final = ft_put_zero(result);
	return (final);
}
void	set_parser2(t_data *data)
{
//teste PIPE
	// ft_lstadd_back_tokens(&(data->tokens), ft_lstnew_tokens(data->tokens,"echo oi", 0));
	// ft_lstadd_back_tokens(&(data->tokens), ft_lstnew_tokens(data->tokens,"|", 1));
	// ft_lstadd_back_tokens(&(data->tokens), ft_lstnew_tokens(data->tokens,"echo foi", 0));
	// ft_lstadd_back_tokens(&(data->tokens), ft_lstnew_tokens(data->tokens,"|", 1));
	// ft_lstadd_back_tokens(&(data->tokens), ft_lstnew_tokens(data->tokens,"ls", 0));
	// ft_lstadd_back_tokens(&(data->tokens), ft_lstnew_tokens(data->tokens,"|", 1));
	// ft_lstadd_back_tokens(&(data->tokens), ft_lstnew_tokens(data->tokens,"pwd", 0));

//teste redirect >
	// ft_lstadd_back_tokens(&(data->tokens), ft_lstnew_tokens(data->tokens, "ls", 0));
	// ft_lstadd_back_tokens(&(data->tokens), ft_lstnew_tokens(data->tokens, ">", 2));
	// ft_lstadd_back_tokens(&(data->tokens), ft_lstnew_tokens(data->tokens, "file1", 0));
	// ft_lstadd_back_tokens(&(data->tokens), ft_lstnew_tokens(data->tokens, ">", 2));
	// ft_lstadd_back_tokens(&(data->tokens), ft_lstnew_tokens(data->tokens, "file2", 0));

//teste redirect <
	// ft_lstadd_back_tokens(&(data->tokens), ft_lstnew_tokens(data->tokens, "cat", 0));
	// ft_lstadd_back_tokens(&(data->tokens), ft_lstnew_tokens(data->tokens, "<", 3));
	// ft_lstadd_back_tokens(&(data->tokens), ft_lstnew_tokens(data->tokens, "arquivo1", 0));
	// ft_lstadd_back_tokens(&(data->tokens), ft_lstnew_tokens(data->tokens, "<", 3));
	// ft_lstadd_back_tokens(&(data->tokens), ft_lstnew_tokens(data->tokens, "arquivo2", 0));
	// ft_lstadd_back_tokens(&(data->tokens), ft_lstnew_tokens(data->tokens, "<", 3));
	// ft_lstadd_back_tokens(&(data->tokens), ft_lstnew_tokens(data->tokens, "arquivo3", 0));
	// ft_lstadd_back_tokens(&(data->tokens), ft_lstnew_tokens(data->tokens, ">", 2));
	// ft_lstadd_back_tokens(&(data->tokens), ft_lstnew_tokens(data->tokens, "fileout", 0));

//teste redirect >>
	// ft_lstadd_back_tokens(&(data->tokens), ft_lstnew_tokens(data->tokens,"echo oi", 0));
	// ft_lstadd_back_tokens(&(data->tokens), ft_lstnew_tokens(data->tokens,">>", 4));
	// ft_lstadd_back_tokens(&(data->tokens), ft_lstnew_tokens(data->tokens,"fileout", 0));

//teste redirect <<
	ft_lstadd_back_tokens(&(data->tokens), ft_lstnew_tokens(data->tokens, "cat", 0));
	ft_lstadd_back_tokens(&(data->tokens), ft_lstnew_tokens(data->tokens, "<<", 5));
	ft_lstadd_back_tokens(&(data->tokens), ft_lstnew_tokens(data->tokens, "testefile", 0));
	ft_lstadd_back_tokens(&(data->tokens), ft_lstnew_tokens(data->tokens, ">", 4));
	ft_lstadd_back_tokens(&(data->tokens), ft_lstnew_tokens(data->tokens, "file2", 0));

	// ft_lstadd_back_tokens(&(data->tokens), ft_lstnew_tokens(data->tokens, ">", 2));
	// ft_lstadd_back_tokens(&(data->tokens), ft_lstnew_tokens(data->tokens, "fileout", 0));
	// ft_putnbr_fd(001,2);
	// char	*result;
	// result = ft_put_zero(ft_itoa(001));
	// printf("entrada:%s saida:%s\n",ft_itoa(001), result);
	// result = ft_put_zero(ft_itoa(002));
	// printf("entrada:%s saida:%s\n",ft_itoa(002), result);
	// result = ft_put_zero(ft_itoa(011));
	// printf("entrada:%s saida:%s\n",ft_itoa(011), result);
	// result = ft_put_zero(ft_itoa(111));
	// printf("entrada:%s saida:%s\n",ft_itoa(111), result);
	// result = ft_put_zero(ft_itoa(999));
	// printf("entrada:%s saida:%s\n",ft_itoa(999), result);

	ft_check_heredoc(data->tokens);

	// exit(0);
	// char buffer[100];
	// read(STDIN_FILENO, buffer, sizeof(buffer));
    // printf("Lido do stdin:");
    // printf("Lido do stdin: %s", buffer);
    // printf("Lido do stdin:");

	data->tree = create_tree(data->tokens);
	// print_tree(data->tree, 1);
}

void	init_read(t_data *data, char *input)
{
	// char	*input_spaces;
	// char	*input_wild;
	// char	**input_remove_spaces;
	// char	wild_char;
	// char	**input_ok;

	// wild_char = do_not_have(input);
	// // printf("wild_char %c\n", wild_char);
	// input_spaces = set_spaces(input);
	// // printf("input_spaces %s\n", input_spaces);
	// // free(input);
	// input_wild = set_wild_char(input_spaces, wild_char);
	// // printf("input_wild %s\n", input_wild);
	// input_remove_spaces = ft_split(input_wild, ' '); // olhar o TAB - ROGER
	// // parray(input_remove_spaces);
	// input_ok = remove_wild_char(input_remove_spaces, wild_char);
	// parray(input_ok);

	set_parser2(data);
}
