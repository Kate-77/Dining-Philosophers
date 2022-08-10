/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoutaou <kmoutaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 02:17:07 by kmoutaou          #+#    #+#             */
/*   Updated: 2022/08/10 12:43:27 by kmoutaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	monitoring(t_infos *infos)
{
	long long		time;

	pthread_mutex_lock(&infos->thanatos);
	if (infos->death == 0)
	{	
		while (infos->death == 0)
		{
			pthread_mutex_unlock(&infos->thanatos);
			pthread_mutex_lock(&infos->lastmeal_protector);
			time = get_time() - infos->philo->last_meal;
			pthread_mutex_unlock(&infos->lastmeal_protector);
			pthread_mutex_lock(&infos->thanatos);
			if (time > infos->time_to_die || infos->death != 0)
			{
				pthread_mutex_unlock(&infos->thanatos);
				display(infos->philo, "died");
				pthread_mutex_lock(&infos->thanatos);
				infos->death = 1;
				pthread_mutex_unlock(&infos->thanatos);
				return (0);
			}
			else
				pthread_mutex_unlock(&infos->thanatos);
			if (infos->number_of_eat != -1)
			{
				pthread_mutex_lock(&infos->protector);
				if (infos->times_eating_done == infos->number_of_philosophers)
				{
					pthread_mutex_unlock(&infos->protector);
					pthread_mutex_lock(&infos->thanatos);
					infos->death = 1;
					pthread_mutex_unlock(&infos->thanatos);
					return (0);
				}
				else
					pthread_mutex_unlock(&infos->protector);
			}
		}
	}
	else
		pthread_mutex_unlock(&infos->thanatos);
	return (1);
}
