/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 11:29:45 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/11/26 16:08:46 by jelvan-d      ########   odam.nl         */
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

typedef struct	s_input
{
	ssize_t	nb_philo;
	ssize_t	ms_to_die;
	ssize_t	ms_to_eat;
	ssize_t	ms_to_sleep;
	ssize_t	times_to_eat;
}				t_input;

typedef struct	s_philo
{
	int				*dead_philosopher;
	ssize_t			i;
	ssize_t			ms_to_die;
	ssize_t			ms_to_eat;
	ssize_t			ms_to_sleep;
	ssize_t			times_to_eat;
	ssize_t			current_time_ms;
	ssize_t			start_time_ms;
	ssize_t			time_last_eaten;
	pthread_t		philosopher;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*write_lock;
}				t_philo;

/*
********************************INITIALISATION.C********************************
*/
int		initialise_mutexes(t_philo *philo, int index, ssize_t nb_philo, 
							pthread_mutex_t *write_lock);
void	initialise_philo(t_input *input, t_philo *philo, int *dead);
void	*initialise_monitoring(void *ptr);
								
/*
*************************************MAIN.C*************************************
*/
int		main(int argc, char **argv);

/*
**********************************PHILOSOPHERS.C********************************
*/
int		philosophers(t_input *data);

/*
*******************************PHILOSOPHER_ACTIONS.C****************************
*/
void	print_message(t_philo *philo, ssize_t time, char *str);
void	eat(t_philo *philo);
void	slep(t_philo *philo);
void	think(t_philo *philo);

/*
*************************************UTILS.C************************************
*/
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
ssize_t	get_time(void);

#endif
