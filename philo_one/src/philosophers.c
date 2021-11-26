/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 16:26:13 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/11/26 16:38:25 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	free_and_return(t_philo *philo, pthread_t *control, int err)
{
	free(philo);
	free(control);
	return (err);
}

static void	*philo_action(void *ptr)
{
	t_philo *philo;

	philo = (t_philo*)ptr;
	philo->start_time_ms = get_time();
	while (!*philo->dead_philosopher)
	{
		eat(philo);
		if (!*philo->dead_philosopher)
			slep(philo);
		if (!*philo->dead_philosopher)
			think(philo);
		if (philo->times_to_eat == 0)
			break ;
	}
	return NULL;
}

static void	philo_initialisation_loop(t_input *input, t_philo *philo,
							pthread_mutex_t	*write_lock, int *dead_philosopher)
{
	int	i;

	i = 0;
	*dead_philosopher = 0;
	pthread_mutex_init(write_lock, NULL);
	while (i < input->nb_philo)
	{
		initialise_philo(input, &philo[i], dead_philosopher);
		initialise_mutexes(philo, i, input->nb_philo, write_lock);
		i++;
	}
}

int			philosophers(t_input *input)
{
	t_philo			*philo;
	pthread_t		*control;
	ssize_t			i;
	pthread_mutex_t	write_lock;
	int				dead_philosopher;

	philo = malloc(sizeof(t_philo) * input->nb_philo);
	control = malloc(sizeof(pthread_t) * input->nb_philo);
	if (!philo || !control)
		return (YOURMOM);
	i = 0;
	philo_initialisation_loop(input, philo, &write_lock, &dead_philosopher);
	while (i < input->nb_philo)
	{
		// initialise_philo(input, philo, &dead_philosopher, &write_lock);
		pthread_create(&philo[i].philosopher, NULL, philo_action, &philo[i]);
		pthread_create(&control[i], NULL, initialise_monitoring, &philo[i]);
		i++;
	}
	i = 0;
	while (i < input->nb_philo)
	{
		if (pthread_join(philo[i].philosopher, NULL) != 0)
			return (free_and_return(philo, control, 1));
		if (pthread_join(control[i], NULL) != 0)
			return (free_and_return(philo, control, 1));
		i++;
	}
	return (free_and_return(philo, control, 0));
}
