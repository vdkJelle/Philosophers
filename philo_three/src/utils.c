/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 12:33:41 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/05/24 13:10:10 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_atoi(const char *str)
{
	int					negative;
	unsigned long int	n;

	n = 0;
	while (*str == ' ')
		str++;
	if (!str)
		return (0);
	negative = (*str == '-');
	if (*str == '-' || *str == '+')
		str++;
	while (*str && ft_isdigit(*str))
	{
		if (n >= 922337203685477580)
		{
			if (!negative)
				return (-1);
			return (0);
		}
		n = n * 10 + (*str - '0');
		str++;
	}
	if (negative)
		return (n * -1);
	return (n);
}

int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}