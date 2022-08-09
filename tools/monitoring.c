/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoutaou <kmoutaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 02:17:07 by kmoutaou          #+#    #+#             */
/*   Updated: 2022/08/09 03:12:23 by kmoutaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	monitoring(t_infos *infos)
{
	long long		time;

	while (infos->death == 0)
	{
		pthread_mutex_lock(&infos->philo->lastmeal_protector);
		time = get_time() - infos->philo->last_meal;
		pthread_mutex_unlock(&infos->philo->lastmeal_protector);
		pthread_mutex_lock(&infos->philo->thanatos);
		if (time > infos->time_to_die || infos->death != 0)
		{
			pthread_mutex_unlock(&infos->philo->thanatos);
			display(infos->philo, "died");
			pthread_mutex_lock(&infos->philo->thanatos);
			infos->death = 1;
			pthread_mutex_unlock(&infos->philo->thanatos);
			return (0);
		}
		else
			pthread_mutex_unlock(&infos->philo->thanatos);
		if (infos->number_of_eat != -1)
		{
			if (infos->times_eating_done == infos->number_of_philosophers)
			{
				pthread_mutex_lock(&infos->philo->thanatos);
				infos->death = 1;
				pthread_mutex_unlock(&infos->philo->thanatos);
				return (0);
			}
		}
	}
	return (1);
}
