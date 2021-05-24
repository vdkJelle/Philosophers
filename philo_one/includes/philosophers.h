/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jelvan-d <jelvan-d@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/24 11:29:45 by jelvan-d      #+#    #+#                 */
/*   Updated: 2021/05/24 17:32:15 by jelvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS
# define PHILOSOPHERS

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
