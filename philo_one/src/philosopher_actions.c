/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher_actions.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/24 11:36:30 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/06/24 12:04:19 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->write_lock);
	philo->current_time_ms = get_time();
	printf("[%.4lu] philosopher [%lu] has taken a fork\n", philo->current_time_ms - philo->start_time_ms, philo->i);
	pthread_mutex_unlock(philo->write_lock);
	pthread_mutex_lock(philo->write_lock);
	philo->current_time_ms = get_time();
	printf("[%.4lu] philosopher [%lu] is eating\n", philo->current_time_ms - philo->start_time_ms, philo->i);
	pthread_mutex_unlock(philo->write_lock);
	usleep(philo->ms_to_eat * 1000);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (philo->times_to_eat != -1)
		philo->times_to_eat--;
	return ;
}

void	slep(t_philo *philo)
{
	pthread_mutex_lock(philo->write_lock);
	philo->current_time_ms = get_time();
	printf("[%.4lu] philosopher [%lu] is sleeping\n", philo->current_time_ms - philo->start_time_ms, philo->i);
	pthread_mutex_unlock(philo->write_lock);
	usleep(philo->ms_to_sleep * 1000);
	return ;
}

void	think(t_philo *philo)
{
	pthread_mutex_lock(philo->write_lock);
	philo->current_time_ms = get_time();
	printf("[%.4lu] philosopher [%lu] is thinking\n", philo->current_time_ms - philo->start_time_ms, philo->i);
	pthread_mutex_unlock(philo->write_lock);
	return ;
}
