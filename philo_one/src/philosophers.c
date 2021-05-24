/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 16:26:13 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/05/24 17:43:50 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	free_and_return(pthread_t *philosophers, int err)
{
	free(philosophers);
	// free(*(err));
	return (err);
}

static void	*philo_action(void *data)
{
	(void)data;
	printf("hello!\n");
	return NULL;
}

int			philosophers(t_data *data)
{
	pthread_t	*philosophers;
	int			i;

	philosophers = malloc(sizeof(pthread_t) * data->nb_philo);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_create(philosophers + i, NULL, philo_action, data);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(philosophers[i], NULL) != 0)
			return (free_and_return(philosophers, 1));
		i++;
	}
	return (free_and_return(philosophers, 0));
}
