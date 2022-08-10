/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoutaou <kmoutaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 02:16:54 by kmoutaou          #+#    #+#             */
/*   Updated: 2022/08/10 12:42:43 by kmoutaou         ###   ########.fr       */
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
	pthread_mutex_lock(&philosopher->philo_infos->lastmeal_protector);
	philosopher->last_meal = get_time();
	pthread_mutex_unlock(&philosopher->philo_infos->lastmeal_protector);
	pthread_mutex_lock(&philosopher->philo_infos->thanatos);
	if (philosopher->philo_infos->death == 0)
	{
		pthread_mutex_unlock(&philosopher->philo_infos->thanatos);
		display(philosopher, "is eating");
	}
	else
		pthread_mutex_unlock(&philosopher->philo_infos->thanatos);
	philosopher->times_eating += 1;
	if (philosopher->times_eating >= philosopher->philo_infos->number_of_eat)
	{
		pthread_mutex_lock(&philosopher->philo_infos->protector);
		philosopher->philo_infos->times_eating_done += 1;
		pthread_mutex_unlock(&philosopher->philo_infos->protector);
	}
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
	pthread_mutex_lock(&philosopher->philo_infos->thanatos);
	if (!philosopher->philo_infos->death)
	{
		while (!philosopher->philo_infos->death)
		{
			pthread_mutex_unlock(&philosopher->philo_infos->thanatos);
			forks(philosopher);
			eating(philosopher);
			sleeping(philosopher);
			thinking(philosopher);
		}
	}
	else
		pthread_mutex_unlock(&philosopher->philo_infos->thanatos);
	return (NULL);
}
