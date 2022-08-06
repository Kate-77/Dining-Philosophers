/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemis <artemis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 01:46:01 by kmoutaou          #+#    #+#             */
/*   Updated: 2022/08/06 16:04:24 by artemis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	check_args(int argc)
{
	if (argc != 5 && argc != 6)
	{	
		printf("Error\n");
		exit(0);
	}
	return ;
}

void	join_philo(data_thread *infos)
{
	int	i;

	i = 0;
	while (i < infos->number_of_philosophers)
	{
		pthread_join(infos->philo->threads[i], NULL);
		i++;
	}
	free(infos->philo);
	return ;
}

void	destroy_mutex(data_thread *infos)
{
	int	i;

	i = 0;
	while (i < infos->number_of_philosophers)
	{
		pthread_mutex_destroy(&infos->forks[i]);
		i++;
	}
	free(infos->forks);
	return ;
}

void	creation(data_thread *infos)
{
	int	i;

	i = 0;
	while (i < infos->number_of_philosophers)
	{
		infos->philo[i].last_meal = infos->start;
		pthread_create(infos->philo->threads, NULL, thread_handler, &infos->philo[i]);
		i++;
	}
	return ;
}

int	main(int argc, char **argv)
{
	data_thread		*infos;

	check_args(argc);
	infos = (data_thread *)malloc(sizeof(data_thread));
	initialize(infos, argc, argv);
	infos->start = get_time();
	creation(infos);
	if (monitoring(infos) == 0)
		return (0);
	join_philo(infos);
	destroy_mutex(infos);
	return (0);
}
