/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoutaou <kmoutaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 02:16:54 by kmoutaou          #+#    #+#             */
/*   Updated: 2022/08/08 00:34:38 by kmoutaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	forks(t_thread *philosopher)
{
	pthread_mutex_lock(&philosopher->philo_infos->forks[philosopher->t_id]);
	display(philosopher, "has taken a fork");
	pthread_mutex_lock(&philosopher->philo_infos->forks[(philosopher->t_id + 1) \
			% philosopher->philo_infos->number_of_philosophers]);
	display(philosopher, "has taken a fork");
	return ;
}

void	eating(t_thread *philosopher)
{
	philosopher->last_meal = get_time();
	if (philosopher->philo_infos->death == 0)
		display(philosopher, "is eating");
	philosopher->times_eating += 1;
	if (philosopher->times_eating >= philosopher->philo_infos->number_of_eat)
		philosopher->philo_infos->times_eating_done += 1;
	p_usleep(philosopher->philo_infos->time_to_eat);
	pthread_mutex_unlock(&philosopher->philo_infos->forks[philosopher->t_id]);
	pthread_mutex_unlock(&philosopher->philo_infos->forks[(philosopher->\
				t_id + 1) % philosopher->philo_infos->number_of_philosophers]);
	return ;
}

void	sleeping(t_thread *philosopher)
{
	display(philosopher, "is sleeping");
	p_usleep(philosopher->philo_infos->time_to_sleep);
	return ;
}

void	thinking(t_thread *philosopher)
{
	display(philosopher, "is thinking");
	return ;
}

void	*thread_handler(void *arg)
{
	t_thread	*philosopher;

	philosopher = arg;
	if (philosopher->t_id % 2 != 0)
		p_usleep(philosopher->philo_infos->time_to_eat);
	while (!philosopher->philo_infos->death)
	{
		forks(philosopher);
		eating(philosopher);
		sleeping(philosopher);
		thinking(philosopher);
	}
	return (NULL);
}
