/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 21:44:41 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/06/01 11:59:23 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	long int	num;
	int			i;
	int			s;

	num = 0;
	i = 0;
	s = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		s = s * (44 - nptr[i]);
		i++;
	}
	while (nptr[i] != '\0' && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		num = num * 10 + (nptr[i] - '0');
		i++;
	}
	return (num * s);
}
