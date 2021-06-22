/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 16:26:13 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/06/23 00:20:14 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	free_and_return(t_philo **philo, int err)
{
	free(*philo);
	return (err);
}

// static void intialise_forks(t_philo *philo, ssize_t index)
// {
	
// }

static void	initialise_philo(t_data *data, t_philo *philo, ssize_t index)
{
	philo->ms_to_die = data->ms_to_die;
	philo->ms_to_eat = data->ms_to_eat;
	philo->ms_to_sleep = data->ms_to_sleep;
	philo->iter = data->iter;
	philo->prev_time_ms = 0;
	philo->time_ms = get_time();
	philo->i = index + 1;
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
		initialise_philo(data, &philo[i], i);
		// initialise_forks(&philo[i], i);
		pthread_create(&philo[i].philosopher, NULL, philo_action, &philo[i]);
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
