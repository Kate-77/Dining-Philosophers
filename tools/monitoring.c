/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoutaou <kmoutaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 02:17:07 by kmoutaou          #+#    #+#             */
/*   Updated: 2022/08/06 04:07:23 by kmoutaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	monitoring_times_eating(data_thread * infos)
{
	while (infos->death == 0)
	{
		//pthread_mutex_lock(&infos->finish_mutex);
		if (infos->times_eating_done == infos->number_of_eat * infos->number_of_philosophers)
		{
			//display(infos->philo, "salina");
			infos->death = 1;
			return (0);
		}
		//pthread_mutex_unlock(&infos->finish_mutex);
	}
	return (1);
}

int	monitoring(th_data *philo)
{
	long long		time;

	while (philo->philo_infos->death == 0)
	{
		time = get_time() - philo->last_meal;
		if (time > philo->philo_infos->time_to_die || philo->philo_infos->death != 0)
		{
			display(philo, "died");
			philo->philo_infos->death = 1;
			return (0); 
		}
	}
	return (1);
}

void	manage_monitoring(data_thread *infos)
{
	if (infos->number_of_eat == 0)
	{
		if (monitoring_times_eating(infos) == 0)
			return ;
	}
	if (monitoring(infos->philo) == 0)
		return ;
}