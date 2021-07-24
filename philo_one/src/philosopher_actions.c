/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher_actions.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/24 11:36:30 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/07/24 12:15:06 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_message(t_philo *philo, ssize_t time, char *str)
{
	ssize_t	curr_time;

	(void)time;
	pthread_mutex_lock(philo->write_lock);
	curr_time = get_time() - philo->start_time_ms;
	if (!*philo->dead_philosopher)
		printf("[%.4lu] %lu %s\n", curr_time, philo->i, str);
	pthread_mutex_unlock(philo->write_lock);
	return ;
}

void		eat(t_philo *philo)
{
	ssize_t curr_time;

	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	curr_time = get_time() - philo->start_time_ms;
	print_message(philo, curr_time, "has taken a fork");
	curr_time = get_time() - philo->start_time_ms;
	philo->time_last_eaten = curr_time;
	print_message(philo, curr_time, "is eating");
	usleep(philo->ms_to_eat * 1000);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (philo->times_to_eat != -1)
		philo->times_to_eat--;
	return ;
}

void		slep(t_philo *philo)
{
	ssize_t curr_time;

	curr_time = get_time() - philo->start_time_ms;
	print_message(philo, curr_time, "is sleeping");
	usleep(philo->ms_to_sleep * 1000);
	return ;
}

void		think(t_philo *philo)
{
	ssize_t curr_time;

	curr_time = get_time() - philo->start_time_ms;
	print_message(philo, curr_time, "is thinking");
	return ;
}
