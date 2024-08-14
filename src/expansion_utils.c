/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 13:52:03 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/08/14 14:57:17 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_strcpy(char *dst, const char *src)
{
	if (src && dst)
	{
		while (*src)
			*dst++ = *src++;
		*dst = '\0';
	}
}

void	utils_expansion2(t_mini *data, char **arg, int i, int j, char **result)
{
	char	*temp1;
	char	*temp2;
	char	*temp3;
	char	*new_result;
	
	temp1 = ft_substr(*arg, i, j - i + 1);
	temp2 = expansion(data, temp1);
	temp3 = ft_calloc(1, ft_strlen(*result) + 1);
	ft_strcpy(temp3, *result);
	free(*result);
	new_result = ft_strjoin(temp3, temp2);
	free(temp1);
	free(temp2);
	free(temp3);
	*result = new_result;
}

void	utils_expansion3(char **result, char *arg, int i)
{
	char	*temp;
	char	*new_result;

	temp = ft_substr(arg, i, 1);
	new_result = ft_strjoin(*result, temp);
	free(*result);
	free(temp); 
	*result = new_result;
}

/* void	utils_expansion(t_data *data, char **arg) */
/* { */
/* 	char	*temp1; */
/* 	char	*temp2; */
/**/
/* 	temp2 = ft_substr(*arg, 1, ft_strlen(*arg) - 2); */
/* 	temp1 = full_expansion(data, temp2); */
/* 	free(*arg); */
/* 	*arg = ft_calloc(1, ft_strlen(temp1) + 1); */
/* 	ft_strcpy(*arg, temp1); */
/* 	free(temp1); */
/* 	free(temp2); */
/* } */
