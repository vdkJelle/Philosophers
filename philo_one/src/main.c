/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 11:41:10 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/07/24 13:12:32 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	check_arguments(int ac, char **av)
{
	int	i;

	while (ac > 1)
	{
		i = 0;
		while (av[ac - 1][i])
		{
			if (ft_isdigit(av[ac - 1][i]) == 0)
				return (YOURMOM);
			i++;
		}
		ac--;
	}
	return (0);
}

static int	parse_arguments(t_input *input, int ac, char **av)
{
	memset(input, -1, sizeof(*input));
	input->nb_philo = ft_atoi(av[1]);
	input->ms_to_die = ft_atoi(av[2]);
	input->ms_to_eat = ft_atoi(av[3]);
	input->ms_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		input->times_to_eat = ft_atoi(av[5]);
	return (0);
}

int	main(int ac, char **av)
{
	t_input input;

	get_time();
	if (ac != 5 && ac != 6)
	{
		printf("Error, wrong amount of arguments\n");
		return (YOURMOM);
	}
	if (check_arguments(ac, av) == -1)
	{
		printf("Error, please provide valid arguments\n");
		return (YOURMOM);
	}
	parse_arguments(&input, ac, av);
	return (philosophers(&input));
}
	// printf("nb_philo = %ld,\t ms_to_die = %ld,\t ms_to_eat = %ld,\t ms_to_sleep = %ld,\t times_to_eat = %ld\n", input.nb_philo, input.ms_to_die, input.ms_to_eat, input.ms_to_sleep, input.times_to_eat);
