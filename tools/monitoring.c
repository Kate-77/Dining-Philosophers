/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemis <artemis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 02:17:07 by kmoutaou          #+#    #+#             */
/*   Updated: 2022/08/06 15:52:18 by artemis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// int	monitoring_times_eating(data_thread * infos)
// {
// 	while (infos->death == 0)
// 	{
// 		if (infos->times_eating_done == infos->number_of_eat * infos->number_of_philosophers)
// 		{
// 			infos->death = 1;
// 			return (0);
// 		}
// 	}
// 	return (1);
// }

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
		if (infos->times_eating_done == infos->number_of_eat * infos->number_of_philosophers)
		{
			infos->death = 1;
			return (0);
		}
	}
	return (1);
}
