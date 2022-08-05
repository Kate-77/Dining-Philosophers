/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoutaou <kmoutaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 02:17:07 by kmoutaou          #+#    #+#             */
/*   Updated: 2022/08/05 04:23:23 by kmoutaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	monitoring_times_eating(data_thread * infos)
{
	while (infos->death == 0)
	{
		pthread_mutex_lock(&infos->finish_mutex);
		if (infos->times_eating_done == infos->number_of_eat * infos->number_of_philosophers)
		{
			//display(infos->philo, "salina");
			infos->death = 1;
			return (0);
		}
		pthread_mutex_unlock(&infos->finish_mutex);
	}
	return (1);
}

int	monitoring(th_data *philo)
{
	struct timeval	now;
	long long		time;

	while (philo->philo_infos->death == 0)
	{
		gettimeofday(&now, NULL);
		time = transform_ms(now) - transform_ms(philo->last_meal);
		if (time >= philo->philo_infos->time_to_die || philo->philo_infos->death != 0)
		{
			philo->philo_infos->death = 1;
			display(philo, "died");
			return (0);
		}
	}
	return (1);
}
