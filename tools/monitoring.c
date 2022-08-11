/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoutaou <kmoutaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 02:17:07 by kmoutaou          #+#    #+#             */
/*   Updated: 2022/08/11 13:25:57 by kmoutaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	monitoring_musteat(t_infos *infos, long long time)
{
	if (time > infos->time_to_die || infos->death != 0)
	{
		pthread_mutex_unlock(&infos->death_protector);
		display(infos->philo, "died");
		pthread_mutex_lock(&infos->death_protector);
		infos->death = 1;
		pthread_mutex_unlock(&infos->death_protector);
		return (0);
	}
	else
		pthread_mutex_unlock(&infos->death_protector);
	if (infos->number_of_eat != -1)
	{
		if (infos->times_eating >= infos->number_of_eat * \
				infos->number_of_philosophers)
		{
			pthread_mutex_lock(&infos->death_protector);
			infos->death = 1;
			pthread_mutex_unlock(&infos->death_protector);
			return (0);
		}
	}
	return (1);
}

int	monitoring(t_infos *infos)
{
	long long		time;

	pthread_mutex_lock(&infos->death_protector);
	if (infos->death == 0)
	{	
		while (infos->death == 0)
		{
			pthread_mutex_lock(&infos->lastmeal_protector);
			time = get_time() - infos->philo->last_meal;
			pthread_mutex_unlock(&infos->lastmeal_protector);
			monitoring_musteat(infos, time);
		}
	}
	else
		pthread_mutex_unlock(&infos->death_protector);
	return (1);
}
