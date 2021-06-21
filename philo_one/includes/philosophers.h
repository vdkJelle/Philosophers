/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 11:29:45 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/06/21 15:14:55 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS
# define PHILOSOPHERS
# define YOURMOM -1

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct	s_data
{
	ssize_t	nb_philo;
	ssize_t	ms_to_die;
	ssize_t	ms_to_eat;
	ssize_t	ms_to_sleep;
	ssize_t	iter;
}				t_data;

typedef struct	s_philo
{
	ssize_t		i;
	ssize_t		ms_to_die;
	ssize_t		ms_to_eat;
	ssize_t		ms_to_sleep;
	ssize_t		iter;
	ssize_t		prev_time_ms;
	ssize_t		time_ms;
	pthread_t	philosopher;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
}				t_philo;

/*
*************************************MAIN.C*************************************
*/
int		main(int argc, char **argv);

/*
**********************************PHILOSOPHERS.C********************************
*/
int		philosophers(t_data *data);

/*
*************************************UTILS.C************************************
*/
int		ft_atoi(const char *str);
int		ft_isdigit(int c);

#endif
