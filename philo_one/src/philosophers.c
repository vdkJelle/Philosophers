/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 16:26:13 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/07/22 17:32:23 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	free_and_return(t_philo **philo, int err)
{
	free(*philo);
	return (err);
}

static void	initialise_philo(t_input *input, t_philo *philo, int *dead,
								pthread_mutex_t *write_lock)
{
	static ssize_t	index = 0;

	philo[index].ms_to_die = input->ms_to_die;
	philo[index].ms_to_eat = input->ms_to_eat;
	philo[index].ms_to_sleep = input->ms_to_sleep;
	philo[index].times_to_eat = input->times_to_eat;
	philo[index].current_time_ms = 0;
	philo[index].start_time_ms = 0;
	philo[index].time_last_eaten = 0;
	philo[index].i = index + 1;
	philo[index].dead_philosopher = dead;
	pthread_mutex_init(&philo[index].left_fork, NULL);
	if (index + 1 == input->nb_philo)
		philo[index].right_fork = &philo[0].left_fork;
	else
		philo[index].right_fork = &philo[index + 1].left_fork;
	philo[index].write_lock = write_lock;
	index++;
}

static void	*monitoring(void *ptr)
{
	t_philo *philo;
	ssize_t	curr_time;

	philo = (t_philo*)ptr;
	curr_time = get_time() - philo->start_time_ms;
	while (curr_time - philo->time_last_eaten <= philo->ms_to_die)
	{
		usleep(500);
		curr_time = get_time() - philo->start_time_ms;
	}
	*philo->dead_philosopher += 1;
	curr_time = get_time() - philo->start_time_ms;
	if (*philo->dead_philosopher == 1)
		printf("[%.4lu] %lu %s\n", curr_time, philo->i, "has died");
	return NULL;
}

static void	*philo_action(void *ptr)
{
	t_philo *philo;

	philo = (t_philo*)ptr;
	philo->start_time_ms = get_time();
	while (!*philo->dead_philosopher)
	{
		eat(philo);
		slep(philo);
		think(philo);
		if (philo->times_to_eat == 0)
			break ;
	}
	return NULL;
}

int			philosophers(t_input *input)
{
	pthread_mutex_t	write_lock;
	t_philo			*philo;
	pthread_t		*control;
	ssize_t			i;
	int				dead_philosopher;

	pthread_mutex_init(&write_lock, NULL);
	philo = malloc(sizeof(t_philo) * input->nb_philo);
	control = malloc(sizeof(pthread_t) * input->nb_philo);
	if (!philo)
		return (YOURMOM);
	i = 0;
	dead_philosopher = 0;
	while (i < input->nb_philo)
	{
		initialise_philo(input, philo, &dead_philosopher, &write_lock);
		i++;
	}
	i = 0;
	while (i < input->nb_philo)
	{
		// initialise_philo(input, philo, &dead_philosopher, &write_lock);
		pthread_create(&philo[i].philosopher, NULL, philo_action, &philo[i]);
		pthread_create(&control[i], NULL, monitoring, &philo[i]);
		i++;
	}
	i = 0;
	while (i < input->nb_philo)
	{
		if (pthread_join(philo[i].philosopher, NULL) != 0)
			return (free_and_return(&philo, 1));
		if (pthread_join(control[i], NULL) != 0)
			return (free_and_return(&philo, 1));
		i++;
	}
	return (free_and_return(&philo, 0));
}
