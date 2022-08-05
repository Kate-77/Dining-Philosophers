/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemis <artemis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 01:48:40 by kmoutaou          #+#    #+#             */
/*   Updated: 2022/08/05 00:59:28 by artemis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	initialize(data_thread *infos, int argc, char **argv)
{
	int	i;

	infos->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
    infos->philo = (th_data *)malloc(sizeof(th_data) * ft_atoi(argv[1]));
	infos->philo->threads = (pthread_t *)malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
	infos->number_of_philosophers = ft_atoi(argv[1]);
    infos->time_to_die = ft_atoi(argv[2]);
	infos->time_to_eat = ft_atoi(argv[3]);
	infos->time_to_sleep = ft_atoi(argv[4]);
	infos->death = 0;
	infos->times_eating_done = 0;
	infos->philo->times_eating = 0;
	if (argc == 6)
		infos->number_of_eat = ft_atoi(argv[5]);
    pthread_mutex_init(&infos->display_mutex, NULL);
	pthread_mutex_init(&infos->finish_mutex, NULL);
    i = 0;
    while (i < infos->number_of_philosophers)
	{
		infos->philo[i].t_id = i;
		pthread_mutex_init(&infos->forks[i], NULL);
		infos->philo[i].philo_infos = infos;
		i++;
	}
	return ;
}
