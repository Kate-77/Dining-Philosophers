/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoutaou <kmoutaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 01:48:40 by kmoutaou          #+#    #+#             */
/*   Updated: 2022/08/11 12:57:03 by kmoutaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	validate_args(int argc, char **argv)
{
	if (ft_atoi(argv[1]) < 0)
	{	
		printf("Error number of philosophers");
		return (1);
	}
	if (ft_atoi(argv[2]) < 0)
	{	
		printf("Error time to die");
		return (1);
	}
	if (ft_atoi(argv[3]) < 0)
	{	
		printf("Error time to eat");
		return (1);
	}
	if (ft_atoi(argv[4]) < 0)
	{	
		printf("Error time to sleep");
		return (1);
	}
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) < 1)
		{	
			printf("Error number of times each philosopher must eat");
			return (1);
		}
	}
	return (0);
}

void	init_threads(t_infos *infos)
{
	int	i;

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

int	initialize(t_infos *infos, int argc, char **argv)
{
	if (validate_args(argc, argv) == 1)
		return (1);
	infos->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
			* ft_atoi(argv[1]));
	infos->philo = (t_thread *)malloc(sizeof(t_thread) * ft_atoi(argv[1]));
	infos->philo->threads = (pthread_t *)malloc(sizeof(pthread_t) \
			* ft_atoi(argv[1]));
	infos->times_eating = 0;
	infos->death = 0;
	infos->number_of_philosophers = ft_atoi(argv[1]);
	infos->time_to_die = ft_atoi(argv[2]);
	infos->time_to_eat = ft_atoi(argv[3]);
	infos->time_to_sleep = ft_atoi(argv[4]);
	infos->times_eating_done = 0;
	if (argc == 6)
		infos->number_of_eat = ft_atoi(argv[5]);
	else
		infos->number_of_eat = -1;
	pthread_mutex_init(&infos->display_protector, NULL);
	pthread_mutex_init(&infos->lastmeal_protector, NULL);
	pthread_mutex_init(&infos->death_protector, NULL);
	pthread_mutex_init(&infos->nbeatingdone_protector, NULL);
	init_threads(infos);
	return (0);
}
