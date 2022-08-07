/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoutaou <kmoutaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 02:17:07 by kmoutaou          #+#    #+#             */
/*   Updated: 2022/08/08 00:11:18 by kmoutaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	monitoring(data_thread *infos)
{
	long long		time;

	while (infos->death == 0)
	{
		time = get_time() - infos->philo->last_meal;
		if (time > infos->time_to_die || infos->death != 0)
		{
			display(infos->philo, "died");
			infos->death = 1;
			return (0); 
		}
		if (infos->number_of_eat != -1)
		{
			if (infos->times_eating_done == infos->number_of_philosophers)
			{
				infos->death = 1;
				return (0);
			}
		}
	}
	return (1);
}
