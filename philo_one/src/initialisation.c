/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialisation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/26 15:18:18 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/11/26 16:28:40 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int		initialise_mutexes(t_philo *philo, int index, ssize_t nb_philo, 
							pthread_mutex_t *write_lock)
{
	if (pthread_mutex_init(&philo[index].left_fork, NULL))
		return(YOURMOM);
	if (index + 1 == nb_philo)
		philo[index].right_fork = &philo[0].left_fork;
	else
		philo[index].right_fork = &philo[index + 1].left_fork;
	philo[index].write_lock = write_lock;
	philo[index].i = index + 1;
	return (0);
}

void	initialise_philo(t_input *input, t_philo *philo, int *dead)
{
	philo->ms_to_die = input->ms_to_die;
	philo->ms_to_eat = input->ms_to_eat;
	philo->ms_to_sleep = input->ms_to_sleep;
	philo->times_to_eat = input->times_to_eat;
	philo->current_time_ms = 0;
	philo->start_time_ms = 0;
	philo->time_last_eaten = 0;
	philo->dead_philosopher = dead;
}

void	*initialise_monitoring(void *ptr)
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
	*philo->dead_philosopher = 1;
	curr_time = get_time() - philo->start_time_ms;
	print_message(philo, curr_time, "has died");
	return NULL;
}
