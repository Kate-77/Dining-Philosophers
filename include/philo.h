/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoutaou <kmoutaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 22:46:48 by kmoutaou          #+#    #+#             */
/*   Updated: 2022/08/08 00:39:39 by kmoutaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>

typedef struct t_data
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
	struct t_thread	*philo;
}	t_infos;

typedef struct t_thread
{
	int				t_id;
	int				times_eating;
	long long		last_meal;
	pthread_t		*threads;
	t_infos	*philo_infos;
}	t_thread;

int			ft_isdigit(int c);
int			ft_atoi(const char *str);
void		initialize(t_infos *infos, int argc, char **argv);
void		init_threads(t_infos *infos);
void		*thread_handler(void *arg);
long long	get_time(void);
void		p_usleep(int t);
void		forks(t_thread *philosopher);
void		eating(t_thread *philosopher);
void		sleeping(t_thread *philosopher);
void		thinking(t_thread *philosopher);
void		display(t_thread *philo, char *str);
int			monitoring(t_infos *infos);

#endif
