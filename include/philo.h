/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoutaou <kmoutaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 22:46:48 by kmoutaou          #+#    #+#             */
/*   Updated: 2022/08/05 23:18:53 by kmoutaou         ###   ########.fr       */
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
	pthread_mutex_t	finish_mutex;
	pthread_mutex_t			*forks;
	struct s_data			*philo;
} data_thread;

typedef struct s_data
{
	int				t_id;
	int				times_eating;
	//pthread_mutex_t		*left_fork;
	//pthread_mutex_t		*right_fork;
	//pthread_mutex_t		protector;
	long long		last_meal;
	pthread_t		*threads;
	data_thread		*philo_infos;
} th_data;

int		ft_isdigit(int c);
int		ft_atoi(const char *str);
void	initialize(data_thread *infos, int argc, char **argv);
void	forks(th_data *philosopher);
void	eating(th_data *philosopher);
void	sleeping(th_data *philosopher);
void	thinking(th_data *philosopher);
int		monitoring_times_eating(data_thread * infos);
int		monitoring(th_data *philo);
void	display(th_data *philo, char *str);
long long	get_time(void);
long long	transform_ms(struct timeval t);
void	p_usleep(int t);
long long	transform_ms(struct timeval t);
long long	get_time(void);
void	manage_monitoring(data_thread *infos);

#endif
