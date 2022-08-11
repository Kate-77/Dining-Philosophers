/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoutaou <kmoutaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 01:46:01 by kmoutaou          #+#    #+#             */
/*   Updated: 2022/08/11 12:56:38 by kmoutaou         ###   ########.fr       */
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

void	join_philo(t_infos *infos)
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

void	destroy_mutex(t_infos *infos)
{
	int	i;

	i = 0;
	while (i < infos->number_of_philosophers)
	{
		pthread_mutex_destroy(&infos->forks[i]);
		i++;
	}
	free(infos->forks);
	pthread_mutex_destroy(&infos->display_protector);
	pthread_mutex_destroy(&infos->lastmeal_protector);
	pthread_mutex_destroy(&infos->death_protector);
	pthread_mutex_destroy(&infos->nbeatingdone_protector);
	return ;
}

void	creation(t_infos *infos)
{
	int	i;

	i = 0;
	infos->start = get_time();
	while (i < infos->number_of_philosophers)
	{
		pthread_mutex_lock(&infos->lastmeal_protector);
		infos->philo[i].last_meal = infos->start;
		pthread_mutex_unlock(&infos->lastmeal_protector);
		pthread_create(&infos->philo->threads[i], NULL, thread_handler, \
				&infos->philo[i]);
		i++;
	}
	return ;
}

int	main(int argc, char **argv)
{
	t_infos	*infos;

	check_args(argc);
	infos = (t_infos *)malloc(sizeof(t_infos));
	if (initialize(infos, argc, argv))
		return (0);
	creation(infos);
	if (monitoring(infos) == 0)
	{
		join_philo(infos);
		return (0);
	}
	join_philo(infos);
	destroy_mutex(infos);
	free(infos);
	return (0);
}
