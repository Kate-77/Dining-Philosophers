/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoutaou <kmoutaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 02:16:54 by kmoutaou          #+#    #+#             */
/*   Updated: 2022/08/07 23:57:12 by kmoutaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	forks(th_data *philosopher)
{
	pthread_mutex_lock(&philosopher->philo_infos->forks[philosopher->t_id]);
	display(philosopher, "has taken a fork");
	pthread_mutex_lock(&philosopher->philo_infos->forks[(philosopher->t_id + 1) % philosopher->philo_infos->number_of_philosophers]);
	display(philosopher, "has taken a fork");
	return ;
}

void	eating(th_data *philosopher)
{
	philosopher->last_meal = get_time();
	if (philosopher->philo_infos->death == 0)
		display(philosopher, "is eating");
	philosopher->times_eating += 1;
	if (philosopher->times_eating >= philosopher->philo_infos->number_of_eat)
		philosopher->philo_infos->times_eating_done += 1;
	p_usleep(philosopher->philo_infos->time_to_eat);
	pthread_mutex_unlock(&philosopher->philo_infos->forks[philosopher->t_id]);
	pthread_mutex_unlock(&philosopher->philo_infos->forks[(philosopher->t_id + 1) % philosopher->philo_infos->number_of_philosophers]);
	return ;
}

void	sleeping(th_data *philosopher)
{
	display(philosopher, "is sleeping");
	p_usleep(philosopher->philo_infos->time_to_sleep);
	return ;
}

void	thinking(th_data *philosopher)
{
	display(philosopher, "is thinking");
	return ;
}

void	*thread_handler(void *arg)
{
	th_data	*philosopher;

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
