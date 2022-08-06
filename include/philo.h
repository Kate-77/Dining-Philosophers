/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemis <artemis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 22:46:48 by kmoutaou          #+#    #+#             */
/*   Updated: 2022/08/06 16:06:26 by artemis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
#include <sys/time.h>
#include <string.h>

typedef struct thread_data
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_eat;
	int				number_of_philosophers;
	int				times_eating_done;
	long long		start;
	int				death;
	pthread_mutex_t	display_mutex;
	pthread_mutex_t	*forks;
	struct s_data	*philo;
} data_thread;

typedef struct s_data
{
	int				t_id;
	int				times_eating;
	long long		last_meal;
	pthread_t		*threads;
	data_thread		*philo_infos;
} th_data;

int			ft_isdigit(int c);
int			ft_atoi(const char *str);
void		initialize(data_thread *infos, int argc, char **argv);
void		init_threads(data_thread *infos);
void		*thread_handler(void *arg);
long long	get_time(void);
void		p_usleep(int t);
void		forks(th_data *philosopher);
void		eating(th_data *philosopher);
void		sleeping(th_data *philosopher);
void		thinking(th_data *philosopher);
void		display(th_data *philo, char *str);
int			monitoring(data_thread *infos);

#endif
