/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 16:26:13 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/06/01 11:27:57 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	free_and_return(t_philo **philo, int err)
{
	free(*philo);
	return (err);
}

static void	initialise_philo(t_data *data, t_philo *philo)
{
	philo->ms_to_die = data->ms_to_die;
	philo->ms_to_eat = data->ms_to_eat;
	philo->ms_to_sleep = data->ms_to_sleep;
	philo->iter = data->iter;
	philo->prev_time_ms = 0;
	philo->time_ms = 0;
}

static void	*philo_action(void *ptr)
{
	pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
	t_philo *philo;

	philo = (t_philo*)ptr;
	pthread_mutex_lock(&lock);
	printf("Philo[%ld] reporting in!\n", philo->i);
	pthread_mutex_unlock(&lock);
	return NULL;
}

int			philosophers(t_data *data)
{
	t_philo	*philo;
	ssize_t	i;

	philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!philo)
		return (YOURMOM);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_create(&philo[i].philosopher, NULL, philo_action, &philo[i]);
		initialise_philo(data, &philo[i]);
		philo[i].i = i + 1;
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(philo[i].philosopher, NULL) != 0)
			return (free_and_return(&philo, 1));
		i++;
	}
	return (free_and_return(&philo, 0));
}
